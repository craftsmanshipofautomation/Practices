#include "libc.h"


void select_sort(int *arr, int size)
{
   int largest;
   
   int i, j;
   // totally size - 1 times
   for (i = size; i > 1; --i)
   {
      largest = 0;
      for (j = 1; j < i; ++ j)
      {
         if (arr[largest] < arr[j])
         {
            largest = j;
         }
      }
      
      swap(&arr[i-1], &arr[largest]);
      PRINT(select_sort, arr, size);
   }
}