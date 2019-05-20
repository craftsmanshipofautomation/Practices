#include "libc.h"


void merge(int *arr, int start, int mid, int end)
{
   int llen = mid - start + 1;
   int rlen = end - (mid+1) + 1;
   int left[llen];
   int right[rlen];
   arrncpy(left, arr+start, llen);
   arrncpy(right, arr+mid+1, rlen);
   //printf("\n\n>>> %d, %d <<<\n", start, end);
   //PRINT(arr, arr+start, end-start+1);
   //PRINT(left, left, llen);
   //PRINT(right, right, rlen);
   int i, j, k;
   i = 0; j = 0;
   for (k = start; k <= end; ++k)
   {
      //printf("in loop: i: %d, j: %d, llen: %d, rlen: %d\n", i, j, llen, rlen);
      if (j >= rlen)
      {
         arr[k] = left[i];
         ++i;
         continue;
      }
      if (i >= llen)
      {
         arr[k] = right[j];
         ++j;
         continue;
      }
      if (left[i] <= right[j])
      {
         //printf("^ arr[%d]<-left[%d]\n", k, i);
         arr[k] = left[i];
         ++i;
      }
      else
      {
         //printf("* arr[%d]<-right[%d]\n", k, j);
         arr[k] = right[j];
         ++j;
      }
   }
   //PRINT(arr, arr+start, end-start+1);


}

void merge_r(int *arr, int start, int end)
{
   int mid;
   if (start < end)
   {
      mid = (start + end) / 2;
      merge_r(arr, start, mid);
      merge_r(arr, mid+1, end);
      merge(arr, start, mid, end);
      //printf("had merged [%d, %d] and [%d, %d]\n", start, mid, mid+1, end);
   }
}

void merge_sort(int *arr, int size)
{
   merge_r(arr, 0, size - 1);
}