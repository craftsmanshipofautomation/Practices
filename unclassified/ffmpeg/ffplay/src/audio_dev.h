#ifndef A515C5D66_9134_1397_146E_06A970C22CCE
#define A515C5D66_9134_1397_146E_06A970C22CCE

#include "ftf.h"
#include "parameters.hpp"

class AudioDev
{
    public:
    AudioDev(const SDL_AudioSpec * wanted_spec, SDL_AudioSpec * obtained_spec,  int allowed_changes);
    ~AudioDev();

    AudioParams GetAudioParams() { return audio_src_; }
    SDL_AudioDeviceID GetAudioDeviceID() { return audio_device_id_; }

    private:
    static int GetSupportedAudioParams(void *opaque, int64_t wanted_channel_layout, int wanted_nb_channels, int wanted_sample_rate, struct AudioParams *audio_hw_params);
    SDL_AudioDeviceID audio_device_id_;
    SDL_AudioSpec * obtained_spec_;

    AudioParams audio_src_;


};


#endif /* 515C5D66_9134_1397_146E_06A970C22CCE */
