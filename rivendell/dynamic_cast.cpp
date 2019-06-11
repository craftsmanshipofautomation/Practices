struct Base
{
   virtual void func1() {}
   virtual void func2() {}   
};

struct Derived1: public Base
{
   virtual void func1() {}   
};

struct Derived2: public Base
{
   virtual void func2() {}   
};

int main()
{
   Derived1 d1;
   Derived2 d2;   
   
}