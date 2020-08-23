#ifndef U7ED61C31_C133_F0D4_1087_D1CF05814F51
#define U7ED61C31_C133_F0D4_1087_D1CF05814F51

#include "ftf.h"

namespace F
{

const char* find_extention(const char * path);
AVInputFormat * find_input_format(const char* file_path);
void dump_format(AVFormatContext *ic_, const char* url) noexcept;
AVCodecContext* CreateCodecContext(AVCodecParameters* codecpar, const char *forced_codec_name);
AVFormatContext* CreateAVFormatContext(const char* filename);
int GetStreamIndex(AVFormatContext* ic, enum AVMediaType type) noexcept;
AVCodecParameters* GetCodecParameters(AVFormatContext *ic, int stream_index) noexcept;
}





#endif /* 7ED61C31_C133_F0D4_1087_D1CF05814F51 */
