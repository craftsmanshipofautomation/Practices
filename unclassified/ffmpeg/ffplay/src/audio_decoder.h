#ifndef A9AE4DF80_F133_F0D5_15BE_A439250DD77A
#define A9AE4DF80_F133_F0D5_15BE_A439250DD77A

#include "frame_queue.h"
#include "packet_queue.h"

///< 一次只处理一个 packet
///<
///<只有一个 packet 成员, 没有 packet 数组
class AudioDecoder
{
public:
  AudioDecoder(AVCodecParameters * codecpar, sp<PacketQueue> pq, SDL_cond* cond,
               const char *usr_defined_codec_name = NULL);
  ~AudioDecoder();

  void Start();

  private:
  static int thread_function(void*);

private: // association
  const char *forced_codec_name_;
  int stream_index_;
  AVCodecContext* avctx_;
  sp<PacketQueue> packet_queue_;
  sp<FrameQueue> sample_fq_;

private:
  int Abort();

  ///< 检查, 如果 packet_pending_ (意味着)
  int decode_thread();
  ///< 一个循环
  ///< 如果
  //AVFrame *decode_frame();
  int decode_frame(AVFrame *);

private:


  bool packet_queue_empty()
  {
    //lzlog(pkt_serial_, d);
    //lzlog(packet_queue_->serial(), d);
    return packet_queue_->serial() == pkt_serial_; 
  }

  int finished_;
  ///< 从 packet queue 处最新弹出来(GET)的包
  int pkt_serial_;

  ///< 记录是否有可用的包
  bool packet_pending_;

  AVPacket pkt_;
  AVFrame *frame_;
  bool got_frame_;

  int64_t start_pts_;

  AVRational start_pts_tb_;

  int64_t next_pts_;
  AVRational time_base_;

  AVRational next_pts_tb_;

  SDL_cond* empty_queue_cond_;
  SDL_Thread *decode_tid_;
};
#endif /* 9AE4DF80_F133_F0D5_15BE_A439250DD77A */
