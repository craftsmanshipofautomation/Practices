#include "utils.h"
#include <cstring>

namespace F
{

const char *find_extention(const char *path)
{
    const char *result = path, *prev = result;
    while ((result = std::strchr(result, '.')) != NULL)
    {
        prev = result;
        ++result;
    }
    return ++prev;
}

AVInputFormat *find_input_format(const char *file_path)
{
    int prev_level = av_log_get_level();
    av_log_set_level(AV_LOG_TRACE);
    const char *ext = find_extention(file_path);
    lzlog(ext, s);
    AVInputFormat *file_iformat = av_find_input_format(ext);
    av_log_set_level(prev_level);
    CHECK_NOTNULL(file_iformat);
    return file_iformat;
}

void dump_format(AVFormatContext *ic, const char *url) noexcept
{
    int prev_level = av_log_get_level();
    av_log_set_level(AV_LOG_INFO);
    av_dump_format(ic, 0, url, 0);
    av_log_set_level(prev_level);
}

AVCodecContext *CreateCodecContext(AVCodecParameters *codecpar, const char *forced_codec_name)
{
    int err;
    AVCodec *deduced_codec;
    AVCodecContext *avctx = avcodec_alloc_context3(NULL);
    CHECK_NOTNULL(avctx);
    avcodec_parameters_to_context(avctx, codecpar);
    deduced_codec = avcodec_find_decoder(avctx->codec_id);
    if (forced_codec_name)
        deduced_codec = avcodec_find_decoder_by_name(forced_codec_name);
    if (!deduced_codec)
    {
        avcodec_free_context(&avctx);
        throw AVException("Can't find decoder");
    }

    err = avcodec_open2(avctx, deduced_codec, NULL);
    if (err < 0)
    {
        avcodec_free_context(&avctx);
        throw AVException("Can't open AVCodecContext");
    }
    return avctx;
}

AVFormatContext *CreateAVFormatContext(const char *filename)
{
    int err;
    AVFormatContext *ic = avformat_alloc_context();
    AVInputFormat *iformat_ = find_input_format(filename);
    err = avformat_open_input(&ic, filename, NULL, NULL);
    if (err < 0)
    {
        avformat_free_context(ic);
        throw AVException("Can not open input format context");
    }
    av_format_inject_global_side_data(ic);
    for (int i = 0; i < ic->nb_streams; ++i)
        ic->streams[i]->discard = AVDISCARD_DEFAULT;
    F::dump_format(ic, filename);
    return ic;
}

int GetStreamIndex(AVFormatContext *ic, enum AVMediaType type) noexcept
{
    int stream_index;
    stream_index = av_find_best_stream(ic, type, -1, -1, NULL, 0);
    return stream_index;
}

AVCodecParameters *GetCodecParameters(AVFormatContext *ic, int stream_index) noexcept
{
    if (!ic || stream_index < 0)
    {
        return NULL;
    }
    return ic->streams[stream_index]->codecpar;
}

} // namespace F