#include <memory>

using namespace std;


class C {
    class B;

    class A {
        B f();
    };
};
