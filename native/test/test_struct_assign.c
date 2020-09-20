#include "libc.h"
#include "strlist.h"

typedef 
struct {
    int a;
    int b;
} T;

int main()
{
    T a = {100, 200};
    T b = a;
    lzlog(a.a, d);
    lzlog(a.b, d);
    lzlog(b.a, d);
    lzlog(b.b, d);

}


