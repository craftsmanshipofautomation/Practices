#include <iostream>

using namespace std;

struct Base
{
   Base() { func(); }
   virtual void func() {cout << "Base::func" << endl;}
   virtual ~Base() {}
};

struct Derived : public Base
{
   virtual void func() {cout << "Derived::func" << endl;}   
   virtual ~Derived() {}   
};

void test()
{
   Base *pb = new Derived;
   delete pb;
}

int main()
{
   test(); 
}