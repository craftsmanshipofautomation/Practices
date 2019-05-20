#include "libc.h"


void insert_sort(int *arr, int size)
{
   if (size == 0 || size == 1)
      return;
   
   int i, j, k;
   for (i = 1, j = 0; i < size - 1; ++i)
   {
      for (j = i-1; j >= 0; --j)
      {  
         if (arr[j] <= arr[i])
            break;
      }
      // sorted #### with insertee ^
      // ##^##
      // insert into j+1
      for (k = i - 1; k > j; --k)
      {
         swap(&arr[k+1], &arr[k]);
      }
      
   }
}