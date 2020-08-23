#include "packet_queue.h"

PacketQueue::PacketQueue(int stream_index)
    : stream_index_(stream_index), first_pkt_(NULL), last_pkt_(NULL), size_(0),
      serial_(0), nb_packets_(0), duration_(0), mutex_(SDL_CreateMutex()),
      cond_(SDL_CreateCond()), abort_request_(true)
{
}

PacketQueue::~PacketQueue()
{
   // Flush();
   SDL_DestroyMutex(mutex_);
   SDL_DestroyCond(cond_);
}

void PacketQueue::Abort()
{
   SDL_LockMutex(mutex_);
   abort_request_ = true;
   SDL_CondSignal(cond_);
   SDL_UnlockMutex(mutex_);
}

void PacketQueue::Start()
{
   SDL_LockMutex(mutex_);
   abort_request_ = false;
   ///< 无锁版 Put
   put_private(&flush_pkt);
   SDL_UnlockMutex(mutex_);
}

void PacketQueue::Flush()
{
   Packet *pkt, *pkt1;

   SDL_LockMutex(mutex_);
   for (pkt = first_pkt_; pkt; pkt = pkt1)
      {
         pkt1 = pkt->next;
         av_packet_unref(&pkt->pkt);
         av_freep(&pkt);
      }
   last_pkt_ = NULL;
   first_pkt_ = NULL;
   nb_packets_ = 0;
   size_ = 0;
   duration_ = 0;
   SDL_UnlockMutex(mutex_);
}

int PacketQueue::Get(AVPacket *out_pkt, bool block, int *out_serial)
{
   Packet *pkt1;
   int ret;
   SDL_LockMutex(mutex_);

   for (;;)
      {
         if (abort_request_)
            {
               ret = -1;
               break;
            }

         pkt1 = first_pkt_;
         if (pkt1)
            {
               first_pkt_ = pkt1->next;
               ///< 如果 pk1 是鏈表裏面唯一的元素，那麼
               ///< next 就是NULL
               if (!first_pkt_)
                  last_pkt_ = NULL;
               nb_packets_--;
               size_ -= pkt1->pkt.size + sizeof(*pkt1);
               duration_ -= pkt1->pkt.duration;
               *out_pkt = pkt1->pkt;
               if (out_serial)
                  *out_serial = pkt1->serial;
               pkt1->~Packet(); // die
               ret = 1;
               break;
            }
         else if (!block)
            {
               ret = 0;
               break;
            }
         else
            {
               ///< block
               ///< 如果有 PUSH, 会发出信号
               LOGF("SDL_CondWait");
               SDL_CondWait(cond_, mutex_);
            }
      }
   SDL_UnlockMutex(mutex_);
   return ret;
}

int PacketQueue::Put(AVPacket *pkt)
{
   int ret;

   SDL_LockMutex(mutex_);
   ret = put_private(pkt);
   SDL_UnlockMutex(mutex_);

   if (pkt != &flush_pkt && ret < 0)
      av_packet_unref(pkt);

   return ret;
}

int PacketQueue::put_private(AVPacket *pkt)
{
   ///< 对每个包都进行拷贝, 将 pkt 所指的内容复制到 tmp_pkt 里面
   Packet *tmp_pkt;

   //    lzlog(abort_request_, d);
   if (abort_request_)
      return -1;

   tmp_pkt = (Packet *)av_malloc(sizeof(Packet));
   if (!tmp_pkt)
      return -2;
   ///< 填充; Packet 封装更多属性
   tmp_pkt->pkt = *pkt;
   ///< 放在最后
   tmp_pkt->next = NULL;
   if (pkt == &flush_pkt)
      serial_++;
   tmp_pkt->serial = serial_;

   ///< 没有元素
   if (!last_pkt_)
      first_pkt_ = tmp_pkt;
   else
      ///< 一个元素及以上
      last_pkt_->next = tmp_pkt;

   ///< 新增的元素始终是最后一个元素
   last_pkt_ = tmp_pkt;
   nb_packets_++;
   ///< AVPacket 里面的包含动态内存的指针
   ///< size 记录动态内存的大小
   size_ += tmp_pkt->pkt.size + sizeof(*tmp_pkt);
   duration_ += tmp_pkt->pkt.duration;
   SDL_CondSignal(cond_);
}

int PacketQueue::PutNullPacket()
{
   ///< 这样做避免了 av_malloc
   AVPacket pkt;
   AVPacket *ref = &pkt;
   av_init_packet(ref);
   ref->data = NULL;
   ref->size = 0;
   ref->stream_index = stream_index_;
   return Put(ref);
}

bool PacketQueue::HasEnoughPackets() { return nb_packets_ > MIN_FRAMES; }