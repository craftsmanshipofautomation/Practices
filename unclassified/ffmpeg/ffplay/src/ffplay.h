#ifndef EDC69B3D_5134_1397_B76C_A38757F9C43E
#define EDC69B3D_5134_1397_B76C_A38757F9C43E

#include "video_state.h"
#include "parameters.hpp"

class FFPlay
{
    public:
    FFPlay(const char*);
    ~FFPlay();
    void AudioOpen();
    void RefreshLoop();
    void Run();

    private:
    void video_refresh(double* remaining_time/*out parameter*/);
    void video_display();

    private:
    ///< M
    sp<VideoState> producer_;
    double remaining_time_;
    double last_video_time_;
    enum ShowMode show_mode_;
    ///< V
    SDL_AudioDeviceID audio_dev_id_;
    ///< C

    ///< cache
    AudioParams audio_params_;
};


#endif /* EDC69B3D_5134_1397_B76C_A38757F9C43E */
