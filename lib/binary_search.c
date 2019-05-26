#include "libc.h"

// bad practice
int bsearch_r(int *arr, int start, int end, int target)
{
   int mid = (start + end) / 2;
   if (start == end)
   {
      if (arr[start] == target)
         return start;
      else 
         return -1;
   }
   int ret = bsearch_r(arr, start, mid, target);
   if (ret != -1)
      return ret;
   else
      return bsearch_r(arr, mid + 1, end, target);
}

// so simple... the number guessing game!
int bsearch_i(int *arr, int size, int target)
{
   int start = 0;
   int end = size -1;
   int mid;
   while(start < end)
   {
      mid = (start + end) / 2;
      if (arr[mid] == target)
         return mid;
      else
      {
         if (arr[mid] > target)
            end = mid - 1;
         else
            start = mid + 1;
      }
   }
   return -1;
}

int binary_search(int *arr, int size, int v)
{
   return 
   bsearch_i(arr, size, v);
   //bsearch_r(arr, 0, size - 1, v);
}