#include "def.h"


TEST_BEGIN

TEST(TEST_UTILS, find_ext)
{
    const char* ext = F::find_extention("a.mp4");
    printf("ext: %s\n", ext);
}

TEST(LOG, lazy_log)
{
    int i = 2;
    float d = 1.23456;
    struct A
    {
        const char *str = "abcd";
    };
    A a;
    int *p = &i;
    lzlog(p, p);
    lzlog(i, d);
    lzlog(a.str, s);
    lzlog(d, f);


}


TEST_END