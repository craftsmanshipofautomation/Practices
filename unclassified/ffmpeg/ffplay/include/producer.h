#ifndef EBA6B715_F133_F0D1_1130_61B16BFBC7B7
#define EBA6B715_F133_F0D1_1130_61B16BFBC7B7

#include "ftf.h"
#include "thread/mutex.h"
#include "packet_provider.h"

#include <map>

class VideoState;


class Producer
{

  public:
  Producer();
  ~Producer() {}
    int Init();
    int Run();
    int Seek(int64_t seek_pos);
    void Loop();

  private:
    VideoState *is_;
    AVPacket pkt1_;
    AVPacket *pkt_;

    Mutex wait_mutex_;

    int64_t stream_start_time_;
    ///< 统计
    int pkt_in_play_range_ = 0;

    int64_t pkt_ts_;

    AVDictionary *format_opts_;
    bool seek_by_bytes_;

    int64_t start_time_;
    int64_t duration_;

    PacketProvider *pktpvd_;
    //PacketFilter *pktflt_;
    //PacketReceiver *pktrcv_;
    //PacketDecoder *pktdec_;
};

#endif /* EBA6B715_F133_F0D1_1130_61B16BFBC7B7 */
