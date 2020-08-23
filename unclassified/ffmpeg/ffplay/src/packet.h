#ifndef P5016F798_9133_F0D4_1202_EA5AE44B8F02
#define P5016F798_9133_F0D4_1202_EA5AE44B8F02

#include "ftf.h"

///< initializad in container.cpp
extern AVPacket flush_pkt;

class Packet
{
  public:
    ~Packet();
    //Packet *next();

  public:
    AVPacket pkt;
    Packet *next;
    int serial;
};

#endif /* 5016F798_9133_F0D4_1202_EA5AE44B8F02 */
