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

TEST(initializer, brace_vs_parathesis)
{   
    int a(2);
    int a2{2};
    lzlog(a, d);
    lzlog(a2, d);
    
}


namespace explicit_
{
    struct X {
        X(float f) {
            cout << "xf" << endl;
        }
        X(int i, float f)
        {
            lzlog(i, d);
            lzlog(f, f);            
        }
    };
    struct Y {
        Y(float f) {
            cout << "yf" << endl;
        }
    };
    void func(X, Y) {}
    void func(X) {}
    
}

TEST(constructor, explicit_)
{
    using namespace explicit_;
    func(2.33, 23.33);
    func({1, 2.3});    
}



TEST_END