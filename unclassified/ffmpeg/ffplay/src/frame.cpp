#include "frame.h"


Frame::Frame()
:frame(av_frame_alloc())
{

}

Frame::~Frame()
{
    av_frame_free(&frame);
}

int Frame::reset()
{
    ///< wipe out that shit
    av_frame_unref(frame);
    //avsubtitle_free(&sub);
    return 0;
}