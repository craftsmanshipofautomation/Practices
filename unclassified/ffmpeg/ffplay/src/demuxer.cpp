#include "demuxer.h"
#include "utils.h"

AVPacket flush_pkt = {NULL};

Demuxer::Demuxer(const char *filename)
    : ic_(F::CreateAVFormatContext(filename)),
      audio_stream_index_(F::GetStreamIndex(ic_, AVMEDIA_TYPE_AUDIO)),
      audio_pktq_(std::make_shared<PacketQueue>(audio_stream_index_)),
      read_tid_(NULL), abort_request_(false)
{
   av_init_packet(&flush_pkt);
   flush_pkt.data = (uint8_t *)&flush_pkt;

   audio_codecpar_ = F::GetCodecParameters(ic_, audio_stream_index_);
}

Demuxer::~Demuxer()
{
   SDL_DestroyCond(continue_read_thread_);
   if (read_tid_)
      SDL_WaitThread(read_tid_, NULL);
}

int Demuxer::thread_function(void *cls)
{
   Demuxer *self = static_cast<Demuxer *>(cls);
   self->read_thread();
   return 0;
}

void Demuxer::Start()
{
   audio_pktq_->Start();
   read_tid_ = SDL_CreateThread(thread_function, "read_thread", (void *)this);
   if (!read_tid_)
      throw AVException(SDL_GetError());
}

int Demuxer::read_thread()
{
   AVPacket pkt1, *pkt = &pkt1;
   int ret;

   SDL_mutex *wait_mutex = SDL_CreateMutex();
   for (;;)
      {
         if (abort_request_)
            break;
         ///< TODO: include video&subtitle packet queue
         ///< if too much packet
         if (packet_queue_is_full())
            {
               SDL_LockMutex(wait_mutex);
               SDL_CondWaitTimeout(continue_read_thread_, wait_mutex, 10);
               SDL_UnlockMutex(wait_mutex);
               continue;
            }
         ///< return 0 if OK, < 0 on error or end of file
         ret = av_read_frame(ic_, pkt);
         if (ret < 0)
            {
               ///< 如果文件还没结束, 放入空包
               if ((ret == AVERROR_EOF || avio_feof(ic_->pb)) && !eof_)
                  {
                     audio_pktq_->PutNullPacket();
                     ///< 结束它
                     eof_ = true;
                  }
               if (ic_->pb && ic_->pb->error)
                  break;
               ///< 等待信号
               ///< 发出信号的只有1种情况: seek
               ///< 所以到达终点的时候,它就阻塞在这
               SDL_LockMutex(wait_mutex);
               SDL_CondWaitTimeout(continue_read_thread_, wait_mutex, 10);
               SDL_UnlockMutex(wait_mutex);
               continue;
            }
         else
            {
               eof_ = false;
            }
         ///< TODO: check if in play range
         if (pkt->stream_index == audio_stream_index_)
            {
               audio_pktq_->Put(pkt);
               // lzlog(audio_pktq_->nb_packets(), d);
            }
         else
            {
               if (pkt)
                  av_packet_unref(pkt);
            }
         // if (pkt->stream_index == )
      }

   SDL_DestroyMutex(wait_mutex);
   return 0;
}

bool Demuxer::packet_queue_is_full()
{
   return audio_pktq_->size() > MAX_QUEUE_SIZE;
}

bool Demuxer::have_enough_visible_packets() { return false; }