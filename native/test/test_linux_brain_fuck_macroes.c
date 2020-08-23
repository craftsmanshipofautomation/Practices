#include "libc.h"
#include "list.h"
#include <assert.h>
#include <stddef.h>

struct A
{
    int a;
    char b;
    double c;
};

void test_offsetof()
{
    lzlog(offsetof(struct A, a), d);
    lzlog(offsetof(struct A, b), d);
    lzlog(offsetof(struct A, c), d);
}

void test_container_of()
{

}

int main() 
{
    test_offsetof();
}