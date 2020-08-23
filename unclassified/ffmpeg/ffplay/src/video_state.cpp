#include "video_state.h"
#include "audio_decoder.h"
#include "packet.h"
#include "utils.h"

VideoState::VideoState(const char *filename)
    : demuxer_(std::make_shared<Demuxer>(filename))
      //, continue_read_thread_(SDL_CreateCond())
      //, audio_packet_queue_(std::make_shared<PacketQueue>(audio_stream_))
      //, sample_frame_queue_(std::make_shared<FrameQueue>(audio_packet_queue_,
      //SAMPLE_QUEUE_SIZE, true))
      ,
      audio_decoder_(std::make_shared<AudioDecoder>(
          demuxer_->audio_codecpar(), demuxer_->audio_packet_queue(),
          demuxer_->continue_read_thread()))
{
}

VideoState::~VideoState() {}

int VideoState::Init()
{
   demuxer_->Start();
   audio_decoder_->Start();
   // audio_dev_->Start();
   return 0;
}

int VideoState::set_flags() { return -1; }