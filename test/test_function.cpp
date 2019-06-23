#include "libcxx.h"

using namespace std;

TEST_BEGIN

// curious overloading with auto as return type

void f(double)
{
}

template<typename T>
auto p(T t) -> decltype(f(t))
{
    cout << "1st" << endl;;
}

template<>
auto p<int>(int i) -> decltype(f(i))
{
    cout << "2nd" << endl;;
}


TEST(DECLTYPE, type_of_function_that_dose_not_exist)
{
    p(2);
}

void f1(int a, int b) {}
int f2(int a, int b) { return 1;}

TEST(STD_FUNCTION, MORE_THAN_2_ARGUMENTS)
{
    using fclass = function<void(int, int)>;
    fclass fobj = f1;
    fobj(1, 2);
    typename fclass::first_argument_type i;
}


TEST_END