#include "libc.h"

int main()
{
   int a1[10] = {9, 1, -2, 3, 2, 5, 8, 90, 6, 10};
   int a2[11] = {1, 3, 5, 7, 9, 11, 2, 4, 6, 8, 10};
   int a3[11] = {1, 3, 5, 7, 9, 11, 2, 4, 6, 8, 10};
   int a4[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
   int a5[11] = {1, 3, 5, 7, 9, 11, 2, 4, 6, 8, 10};
   

   merge_sort(a1, 10);
   PRINT(merge_sort, a1, 10);
   quicksort(a2, 11);
   PRINT(quicksort1, a2, 11);

   lzlog(heap_height(15), d);
   lzlog(heap_height(8), d);
   lzlog(heap_height(16), d);
   lzlog(number_span(1), d);
   lzlog(number_span(123), d);
   lzlog(number_span(14523), d);
   lzlog(number_span(-14523), d);
   
   //print_heap(a4, 10);
   heap_sort(a4, 10);
   PRINT(heapsort, a4, 11);
   
   insert_sort(a5, 11);
   PRINT(insert_sort, a5, 11);
   
   int a6[10] = {9, 1, -2, 3, 2, 5, 8, 90, 6, 10};
   
   bubble_sort(a6, 10);
   int a7[10] = {9, 1, -2, 3, 2, 5, 8, 90, 6, 10};   
   select_sort(a7, 10);
   
   
   
}