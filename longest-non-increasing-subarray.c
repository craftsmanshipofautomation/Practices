#include "libc.h"

int *LongestNonIncreasingSubarray(int *arr, int size, int *len_)
{
   int len = 1, maxlen = 1, maxi = 0, i;
   int *ret;
   if (size == 0)
   {
      len_ = 0;
      return NULL;
   }
lzlog(1,d);
   for (i = 1; i < size; ++i)
   {
      if (arr[i] <= arr[i - 1])
      {
         lzlog(i, d);
         ++len;
      }
      else
      {
         lzlog(len, d);

         if (len > maxlen)
         {
            maxlen = len;
            maxi = i - 1;
            len = 1;
         }
      }
   }
   if (len > maxlen)
   {
      maxlen = len;
      maxi = i - 1;
      len = 1;
   }
   
   *len_ = maxlen;
   ret = malloc(sizeof(int) * maxlen);
   arrncpy(ret, arr + maxi - maxlen + 1, maxlen);
   return ret;
}

#define N 13
int main()
{
   int arr[N] = {2, 5, 3, 2, 1 ,2,10,9, 8,7 ,6,5,4};
   int arr2[0];
   int arr3[2] = {1, 0};
   int arr4[4] = {1, 2, 3, 4};   
   int len;
   int *res = LongestNonIncreasingSubarray(arr4, 4, &len);
   lzlog(len, d);
   PRINT(LongestNonIncreasingSubarray, res, len);
   if (res)
      free(res);
}