#include "test_pimpl.h"


class C::B
{
};

C::B C::A::f()
{
   return B();
}


int main()
{
   C c;
}
