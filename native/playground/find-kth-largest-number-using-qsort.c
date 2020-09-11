#include "libc.h"

int partition(int *arr, int start, int end)
{
   int size = end - start + 1;
   if (size == 1)
      return start;
   int i = start - 1, j = start;   
   int pivot = arr[end];
   while (j < end)
   {
      if (arr[j] < pivot)
      {
         ++i;
         swap(arr + j, arr + i);
      }
      ++j;
   }
   swap(arr + i + 1, arr + end);
   return i + 1;
}

// k:[1, inf)
int find_kth(int *arr, int size, int k)
{
   if (k < 1 || k > size)
      return -1;
   int p, start = 0, end = size - 1;
   int k2 = k-1;
   while(1)
   {
      p = partition(arr, start, end);
      if (p == k2)
         break;
      else if (p > k2)
         end = p - 1;
      else
         start = p + 1;
   }   
   return arr[p];
}

int arr[10] = {0, 1, 6, 3, 9, 5, 2, 7, 8, 4};
void test(int i)
{
   int r = find_kth(arr, 10, i);
   lzlog(r, d);
   assert(i-1 == r);
}

int main()
{
   int i;
   for (i = 1; i < 11; ++i)
      test(i);
}