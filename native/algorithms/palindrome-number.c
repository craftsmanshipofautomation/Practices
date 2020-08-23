#include "libc.h"


bool isPalindrome(int x)
{
   if (x < 0)
      return false;
   int curr = x;
   int len = 0;
   int nums[32] = {0};
   int r;
   int i;
   while (curr > 9)
      {
         r = curr % 10;
         nums[len] = r;
         curr = curr / 10;
         ++len;
      }
   nums[len] = curr;
   ++len;
   for (i = 0; i < len / 2; ++i)
      {
         if (nums[i] != nums[len - 1 - i])
            {
               return false;
            }
      }
   return true;
}

int main()
{
   printf("%d\n", isPalindrome(1000));
   printf("%d\n", isPalindrome(1001));
   printf("%d\n", isPalindrome(1221));
   printf("%d\n", isPalindrome(1000));

}