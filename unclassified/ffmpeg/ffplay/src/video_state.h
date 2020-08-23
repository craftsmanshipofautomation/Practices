#ifndef C574F24A4_A133_F0D1_F73F_2B7F840E7E26
#define C574F24A4_A133_F0D1_F73F_2B7F840E7E26

#include "frame_queue.h"
#include "ftf.h"
#include "audio_decoder.h"
#include "parameters.hpp"
#include "audio_dev.h"
#include "demuxer.h"

class VideoState
{
  public:
    VideoState(const char *filename);
    ~VideoState();
    int Init();
    int Demux();

  bool has_audio() {return true;}
  bool has_video() {return false;}

  private:


    ///> seek, speed, etc
    int set_flags();

  private:
    ///< 有毒， 要考慮初始化順序
    const char *filename_;

    sp<Demuxer> demuxer_;
    sp<AudioDecoder> audio_decoder_;
    //sp<AudioDev> audio_dev_;


    ///< flags
    int paused_;
    int last_paused_;
    ///< from av_read_pause;
    int read_pause_return_;
    SDL_Thread *read_tid_;
    ///< flags
    bool abort_request_;
    bool eof_;

    ///< 交付
    AudioParams audio_tgt_;


};








#endif /* 574F24A4_A133_F0D1_F73F_2B7F840E7E26 */
