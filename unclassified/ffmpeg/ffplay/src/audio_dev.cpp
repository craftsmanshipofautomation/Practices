#include "audio_dev.h"

/*
AudioDev::AudioDev(sp<AudioContext> avctx) {
  int sample_rate = avctx->sample_rate;
  int nb_channels = avctx->channels;
  uint64_t channel_layout = avctx->channel_layout;

    int ret;

    if ((ret = audio_open(this, channel_layout, nb_channels, sample_rate, &audio_src_)) < 0)
        goto fail;
    
    audio_hw_buf_size = ret;
    audio_buf_index = 0;
    audio_buf_index = 0;

    

  audio_device_id_ = SDL_OpenAudioDevice(NULL, 0);
  if (!audio_device_id_) {
  }
}

AudioDev::~AudioDev() { SDL_CloseAudioDevice(audio_device_id_); }

int AudioDev::GetSupportedAudioParams(void *opaque,
                                      int64_t wanted_channel_layout,
                                      int wanted_nb_channels,
                                      int wanted_sample_rate,
                                      struct AudioParams *audio_hw_params) {
  SDL_AudioSpec wanted_spec, spec;
  static const int next_nb_channels[] = {0, 0, 1, 6, 2, 6, 4, 6};
  static const int next_sample_rates[] = {0, 44100, 48000, 96000, 192000};
  int next_sample_rate_idx = FF_ARRAY_ELEMS(next_sample_rates) - 1;

  if (!wanted_channel_layout ||
      wanted_nb_channels !=
          av_get_channel_layout_nb_channels(wanted_channel_layout)) {
    wanted_channel_layout = av_get_default_channel_layout(wanted_nb_channels);
    wanted_channel_layout &= ~AV_CH_LAYOUT_STEREO_DOWNMIX;
  }
  wanted_nb_channels = av_get_channel_layout_nb_channels(wanted_channel_layout);
  wanted_spec.channels = wanted_nb_channels;
  wanted_spec.freq = wanted_sample_rate;
  if (wanted_spec.freq <= 0 || wanted_spec.channels <= 0) {
    av_log(NULL, AV_LOG_ERROR, "Invalid sample rate or channel count!\n");
    return -1;
  }
  while (next_sample_rate_idx &&
         next_sample_rates[next_sample_rate_idx] >= wanted_spec.freq)
    next_sample_rate_idx--;
  wanted_spec.format = AUDIO_S16SYS;
  wanted_spec.silence = 0;
  wanted_spec.samples =
      FFMAX(SDL_AUDIO_MIN_BUFFER_SIZE,
            2 << av_log2(wanted_spec.freq / SDL_AUDIO_MAX_CALLBACKS_PER_SEC));
  wanted_spec.callback = sdl_audio_callback;
  wanted_spec.userdata = opaque;
  while (
      !(audio_dev = SDL_OpenAudioDevice(NULL, 0, &wanted_spec, &spec,
                                        SDL_AUDIO_ALLOW_FREQUENCY_CHANGE |
                                            SDL_AUDIO_ALLOW_CHANNELS_CHANGE))) {
    av_log(NULL, AV_LOG_WARNING, "SDL_OpenAudio (%d channels, %d Hz): %s\n",
           wanted_spec.channels, wanted_spec.freq, SDL_GetError());
    wanted_spec.channels = next_nb_channels[FFMIN(7, wanted_spec.channels)];
    if (!wanted_spec.channels) {
      wanted_spec.freq = next_sample_rates[next_sample_rate_idx--];
      wanted_spec.channels = wanted_nb_channels;
      if (!wanted_spec.freq) {
        av_log(NULL, AV_LOG_ERROR,
               "No more combinations to try, audio open failed\n");
        return -1;
      }
    }
    wanted_channel_layout = av_get_default_channel_layout(wanted_spec.channels);
  }
  if (spec.format != AUDIO_S16SYS) {
    av_log(NULL, AV_LOG_ERROR,
           "SDL advised audio format %d is not supported!\n", spec.format);
    return -1;
  }
  if (spec.channels != wanted_spec.channels) {
    wanted_channel_layout = av_get_default_channel_layout(spec.channels);
    if (!wanted_channel_layout) {
      av_log(NULL, AV_LOG_ERROR,
             "SDL advised channel count %d is not supported!\n", spec.channels);
      return -1;
    }
  }

  audio_hw_params->fmt = AV_SAMPLE_FMT_S16;
  audio_hw_params->freq = spec.freq;
  audio_hw_params->channel_layout = wanted_channel_layout;
  audio_hw_params->channels = spec.channels;
  audio_hw_params->frame_size = av_samples_get_buffer_size(
      NULL, audio_hw_params->channels, 1, audio_hw_params->fmt, 1);
  audio_hw_params->bytes_per_sec = av_samples_get_buffer_size(
      NULL, audio_hw_params->channels, audio_hw_params->freq,
      audio_hw_params->fmt, 1);
  if (audio_hw_params->bytes_per_sec <= 0 || audio_hw_params->frame_size <= 0) {
    av_log(NULL, AV_LOG_ERROR, "av_samples_get_buffer_size failed\n");
    return -1;
  }
  return spec.size;
}

*/