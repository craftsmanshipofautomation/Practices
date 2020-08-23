#include "audio_decoder.h"
#include "utils.h"

AudioDecoder::AudioDecoder(AVCodecParameters *codecpar, sp<PacketQueue> pq,
                           SDL_cond *cond, const char *usr_defined_codec_name)
    : packet_queue_(std::move(pq)),
      sample_fq_(
          std::make_shared<FrameQueue>(packet_queue_, SAMPLE_QUEUE_SIZE, true)),
      empty_queue_cond_(cond), forced_codec_name_(usr_defined_codec_name),
      got_frame_(0), decode_tid_(NULL), pkt_serial_(-1),
      start_pts_(AV_NOPTS_VALUE)
{
   avctx_ = F::CreateCodecContext(codecpar, forced_codec_name_);
}

AudioDecoder::~AudioDecoder()
{
   if (decode_tid_)
      SDL_WaitThread(decode_tid_, NULL);
   sample_fq_->Signal();
}

int AudioDecoder::thread_function(void *cls)
{
   AudioDecoder *self = static_cast<AudioDecoder *>(cls);
   self->decode_thread();
   return 0;
}

void AudioDecoder::Start()
{
   decode_tid_ =
       SDL_CreateThread(thread_function, "decode_thread", (void *)this);
   if (!decode_tid_)
      throw AVException(SDL_GetError());
}

int AudioDecoder::decode_thread()
{
   LOGF("enter audio thread");
   ///< NO data now, try again later(non-blocking io)
   AVRational timebase;
   Frame *af;
   AVFrame *frame;
   int got_frame = 0;
   int ret = 0;
   int64_t cnt = 0;

   frame = av_frame_alloc();
   if (!frame)
      return AVERROR(ENOMEM);
   do
      {
         LOGF("AUDIO THREAD LOOP");
         if (got_frame = decode_frame(frame))
            {
               lzlog(frame, p);
               lzlog(got_frame, d);
               goto the_end;
            }
         if (got_frame)
            {
               ++cnt;
               lzlog(cnt, d);
               timebase = (AVRational){1, frame->sample_rate};
               ///< wait for a writable position
               if (!(af = sample_fq_->PeekWritable()))
                  {
                     LOGF("av_frame_free");
                     av_frame_free(&frame);
                     lzline();
                     return -2;
                  }
               lzline();
               af->pts = (frame->pts == AV_NOPTS_VALUE)
                             ? NAN
                             : frame->pts * av_q2d(timebase);
               af->pos = frame->pkt_pos;
               af->serial = pkt_serial_;
               af->duration =
                   av_q2d((AVRational){frame->nb_samples, frame->sample_rate});
               lzline();

               ///< 讓 af 接管 frame
               ///< af 是從 sample queue 處要來的
               LOGF("av_frame_move_ref");
               av_frame_move_ref(af->frame, frame);
               ///< 填充了 af，size+1
               ///< TODO: 改掉這個接口
               ///< 後知後覺， 增加一個計數
               LOGF("sample_fq_->Push");
               sample_fq_->Push();
            }
      }
   while (ret >= 0 || ret == AVERROR(EAGAIN) || ret == AVERROR_EOF);

the_end:
   LOGF("exit audio thread");
   av_frame_free(&frame);
   return ret;
}

int AudioDecoder::decode_frame(AVFrame *frame)
{
   int ret = AVERROR(EAGAIN);
   AVPacket tmp_pkt;
   for (;;)
      {
         LOGF("AudioDecoder::decode");
         if (packet_queue_empty())
            {
               LOGF("PKTQ EMPTY");
               do
                  {
                     LOGF("PKTQ EMPTY DO WHILE");
                     if (packet_queue_->abort_request())
                        {
                           LOGF("PKTQ ABORT");
                           return -1;
                        }
                     ret = avcodec_receive_frame(avctx_, frame);
                     if (ret >= 0)
                        {
                           LOGF("avcodec_receive_frame SUCCEED");
                           AVRational frm_tb =
                               (AVRational){1, frame->sample_rate};
                           lzline();
                           if (frame->pts != AV_NOPTS_VALUE)
                              ///< 在不同的 timebase 下有不同的 pts
                              frame->pts = av_rescale_q(
                                  frame->pts, avctx_->pkt_timebase, frm_tb);
                           else if (next_pts_ != AV_NOPTS_VALUE)
                              ///< 如果這一幀的 pts 參數缺失
                              frame->pts =
                                  av_rescale_q(next_pts_, next_pts_tb_, frm_tb);
                           if (frame->pts != AV_NOPTS_VALUE)
                              {
                                 ///< wtf??
                                 next_pts_ = frame->pts + frame->nb_samples;
                                 next_pts_tb_ = frm_tb;
                              }
                           lzline();
                        }
                     if (ret == AVERROR_EOF)
                        {
                           LOGF("AVERROR_EOF");
                           finished_ = pkt_serial_;
                        }
                     if (ret >= 0)
                        {
                           lzline();
                           return 1;
                        }
                  }
               while (ret != AVERROR(EAGAIN));
            }

         do
            {
               LOGF("PKTQ HAS PACKETS");
               // lzlog(empty_queue_cond_, p);
               // lzlog(packet_queue_, p);
               lzlog(packet_queue_->nb_packets(), d);
               if (packet_queue_->nb_packets() == 0)
                  ///< signal whoever that waits for queue to be empty
                  SDL_CondSignal(empty_queue_cond_);
               if (packet_pending_)
                  {
                     LOGF("packet_pending_ == true");
                     ///< if there is a packet awaiting
                     ///< that packet is pkt_
                     av_packet_move_ref(&tmp_pkt, &pkt_);
                     packet_pending_ = 0;
                  }
               else
                  {
                     LOGF("packet_pending_ == false");
                     if (packet_queue_->Get(&tmp_pkt, 1, &pkt_serial_) < 0)
                        {
                           lzlog(pkt_serial_, d);
                           return -1;
                        }
                  }
            }
         while (!packet_queue_empty());

         ///< 如果遇到终止符(用一个 flush_pkt 表示EOF)
         if (tmp_pkt.data == flush_pkt.data)
            {
               LOGF("FLUSH PACKET");
               ///< seeking 的时候或者切换到不同的流的时候应该调这个方法
               avcodec_flush_buffers(avctx_);
               finished_ = 0;
               next_pts_ = start_pts_;
               next_pts_tb_ = start_pts_tb_;
            }
         else
            {
               LOGF("NOT FLUSH PKT");
               ///< Supply raw packet data as input to a decoder.
               ///< tmp_pkt 是一个单独的 single video frame
               ///< 或者是若干完整的 audio frame
               ///< 如果是有若干的 frame, 则需要多次调用
               if (avcodec_send_packet(avctx_, &tmp_pkt) == AVERROR(EAGAIN))
                  {
                     lzlog(AVERROR(EAGAIN), d);
                     packet_pending_ = 1;
                     ///< 将 tmp_pkt 的内容转移到 pkt_ 上
                     LOGF("av_packet_move_ref");
                     av_packet_move_ref(&pkt_, &tmp_pkt);
                  }
               ///< wipe the packet
               LOGF("av_packet_unref");
               av_packet_unref(&tmp_pkt);
            }
      } // end for
}