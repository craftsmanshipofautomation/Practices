#include "libc.h"


int partition(int *arr, int start, int end)
{
   int i, j, pivot;
   pivot = arr[end];
   i = start - 1;
   for (j = start; j < end; ++j)
   {
      if (arr[j] <= pivot)
      {
         ++i;
         swap(&arr[i], &arr[j]);
      }
   }
   swap(&arr[i+1], &arr[end]);
   return i+1;
}


void qsr(int *arr, int start, int end)
{
   int p;
   while (start < end)
   {
      p = partition(arr, start, end);
      qsr(arr, start, p-1);
      start = p + 1;
   }
}

void quicksort(int *arr, int size)
{
   qsr(arr, 0, size - 1);

}