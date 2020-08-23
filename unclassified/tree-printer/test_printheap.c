#include "printheap.h"
#include <stdlib.h>
#include <stdio.h>

void test_print_leaf()
{
   int a1[2] = {0, -1234567};
   heap_string_t h = hstr_leaf(a1, 1, 1);
   hstr_print(h);
   hstr_free(h);
}

void test_print_heap(int n, int max)
{
   int a1[n+1];
   int i, r;
   for (i = 0; i <= n; ++i)
   {
      r = rand() % max;
      a1[i] = r * ((r % 2) ? (-1) : 1);
   }
   print_heap(a1, n);
}


void test_print_heap2()
{
   int a1[4] = {0, 1, 22, 3};
   print_heap(a1, 3);
}

int main()
{
   test_print_heap(42, 42);
   printf("\n");
   test_print_heap(99, 10);
   printf("\n");   
   test_print_heap(20, 2323232323);   
}
