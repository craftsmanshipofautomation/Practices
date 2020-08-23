#ifndef B7924E6B_0134_1397_1160_48DA2EF891A0
#define B7924E6B_0134_1397_1160_48DA2EF891A0

#include "ftf.h"


///< medias used among modules

struct AudioParams
{
    int freq;
    int channels;
    int64_t channel_layout;
    enum AVSampleFormat fmt;
    int frame_size;
    int bytes_per_sec;
};





#endif /* B7924E6B_0134_1397_1160_48DA2EF891A0 */
