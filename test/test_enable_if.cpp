#include "libcxx.h"

using namespace std;

TEST_BEGIN

template <typename T> struct A
{
};

template <> struct A<int>
{
    void i(){};
};

template <> struct A<double>
{
    void d(){};
};

TEST(TEMPLATE, SPECIFICATIONS)
{
    A<int> a;
    a.i();
    A<double> b;
    b.d();
}

TEST_END