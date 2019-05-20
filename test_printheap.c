#include "libc.h"


void test_print_leaf()
{
   int a1[2] = {0, -1234567};
   heap_string_t h = hstr_leaf(a1, 1, 1);
   hstr_print(h);
   hstr_free(h);
}

void test_print_heap(int n)
{
   int a1[n+1];
   int i;
   for (i = 0; i <= n; ++i)
      a1[i] = rand() % 30;
   print_heap(a1, n);
}


void test_print_heap2()
{
   int a1[4] = {0, 1, 22, 3};
   print_heap(a1, 3);
}

int main()
{
   test_print_heap(42);
   test_print_heap(43);
}