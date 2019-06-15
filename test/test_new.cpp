#include "libcxx.h"

using namespace std;
TEST_BEGIN

TEST(NEW, size)
{
    struct X
    {
        void *operator new(size_t sz, int i)
        {
            lzlog(sz, d);
            lzlog(i, d);
            return NULL;
        }
        void *operator new[](size_t sz, float f)
        {
            lzlog(sz, d);
            lzlog(f, f);
            return NULL;
        }
    };
    X *p = new(2) X;
    X *p2 = new(3.1415) X[20];
    
}

TEST_END