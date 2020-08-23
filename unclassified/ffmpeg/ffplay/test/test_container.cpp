#include "def.h"

TEST_BEGIN
/*
struct A
{
    A(sp<AVFormatContext> i)
    : ic(std::move(i))
    {}
    sp<AVFormatContext> ic;
};

struct B
{
    B(sp<AVFormatContext> i)
    : ic(std::move(i))
    {}
    sp<AVFormatContext> ic;
};

struct C
{
    C(sp<AVFormatContext> i)
    : ic(std::move(i))
    {}
    sp<AVFormatContext> ic;
};


TEST(SRC, container)
{
    Container ct("/home/root_/Pictures/DARKSOUL.mp4");
    sp<AVFormatContext> ic = ct.GetFormatContext();
    {
        A a(ct.GetFormatContext());
        B b(ic);
        {
            C c(ic);
        }
    }

    //container.Demux();
}
*/

TEST_END