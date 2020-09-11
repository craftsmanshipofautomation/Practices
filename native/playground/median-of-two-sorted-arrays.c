#include "libc.h"

double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2,
                              int nums2Size)
{
   int i, j;
   int tempSz, *tempArr;
   int imin, imax;
   int end1, end2;
   int l_max, r_min;
   if (nums1Size > nums2Size)
      {
         tempSz = nums2Size;
         nums2Size = nums1Size;
         nums1Size = tempSz;
         tempArr = nums2;
         nums2 = nums1;
         nums1 = tempArr;
      }
   imin = 0;
   imax = nums1Size;
   while (imin <= imax)
      {
         i = (imin + imax) / 2;
         j = (nums1Size + nums2Size + 1) / 2 - i;
         printf("(1). %d, %d\n", i, j);
         if (i < imax && nums2[j - 1] > nums1[i])
            {
               imin = i + 1;
            }
         else if (i > imin && nums2[j] < nums1[i - 1])
            {
               imax = i - 1;
            }
         else
            {
               printf("(2). %d, %d\n", i, j);
               //   |
               //j-1|j
               if (i == 0) l_max = nums2[j-1];
               else if (j == 0) l_max = nums1[i-1];
               else l_max = MAX(nums2[j-1], nums1[i-1]);

               if ((nums1Size + nums2Size) % 2)
               {
                   break;
               }

               if (i == nums1Size) r_min = nums2[j];
               else if (j == nums2Size) r_min = nums1[i];
               else r_min = MIN(nums2[j], nums1[i]);

               break;
            }
      }
   if ((nums1Size + nums2Size) % 2)
      {
         return l_max;
      }
   else
      return (l_max + r_min) * 1.0 / 2;
}

int main()
{
   
}