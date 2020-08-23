#include "libcxx.h"
#include <type_traits>
using namespace std;

TEST_BEGIN

template <typename T> struct is_int : std::false_type
{
};

template <> struct is_int<int> : std::true_type
{
};

template<typename T, typename enable_if<is_int<T>::value, T>::type = 0>
void func(T t)
{}

template <typename T, int = 0>
void func2(T)
{
    
}

TEST(TEMPLATE, SPECIFICATIONS)
{
    int i = 0;
    double d = 0.0;
    func(i);
    func2(2);
    //func(d);    
}

TEST_END