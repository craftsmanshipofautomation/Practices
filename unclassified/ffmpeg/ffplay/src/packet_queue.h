#ifndef F39AFB8C_5133_F0D4_F7AB_43E0AA804087
#define F39AFB8C_5133_F0D4_F7AB_43E0AA804087

#include "ftf.h"
#include "packet.h"

class PacketQueue
{
 public:
   PacketQueue(int stream_index);
   ~PacketQueue();

   ///< pop
   int Get(AVPacket *pkt, bool block, int *serial);
   int Put(AVPacket *pkt);
   ///< 放入一个空包
   int PutNullPacket();
   ///< 释放队列所有节点的内存,将PacketQueue 本身清零
   ///< 释放链表所有节点的内存
   void Flush();
   void Abort();
   void Start();

   bool HasEnoughPackets();

 private:
   int put_private(AVPacket *);

 private: // association
   int stream_index_;
   Packet *first_pkt_, *last_pkt_;
   int size_;
   int serial_;
   int nb_packets_;
   ///< 所有相关内容消耗的字节数
   int64_t duration_;
   ///< 与最后一个Packet(包含flush_pkt)的序列号一致
   SDL_mutex *mutex_;
   SDL_cond *cond_;
   bool abort_request_;

 public: // getters
   int size() { return size_; }
   int serial() { return serial_; }
   bool abort_request() { return abort_request_; }
   int nb_packets() { return nb_packets_; }
};

#endif /* F39AFB8C_5133_F0D4_F7AB_43E0AA804087 */
