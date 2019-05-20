#include "libc.h"


void heap_sort(int *arr, int size)
{
   build_heap(arr, size);
   int i;
   for (i = size; i > 1; --i)
   {
      // move the root to the partition
      // that is considered to be sorted
      swap(&arr[1], &arr[size]);
      --size;
      max_heapify(arr, size, 1);
   }
}