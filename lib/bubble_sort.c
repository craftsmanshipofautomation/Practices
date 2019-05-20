#include "libc.h"

void bubble_sort(int *arr, int size)
{
   int max = size - 1;
   int i;
   while (max > 1)
   {
      for (i = 0; i < max; ++i)
      {
         if (arr[i] > arr[i+1])
            swap(&arr[i], &arr[i+1]);
            PRINT(bubble, arr, size);
      }
      --max;
   }
}