#include "libc.h"


int power(int n, int m)
{
   if (m == 0)
      return 1;
   else if (m == 1)
      return n;
   else
      return n * power(n, m - 1);
}

void getLimit(int *max_, int *min_)
{
   unsigned int max = 0;
   max = ~max;
   max = max >> 1;
   int min = max;
   min = ~min;
   *max_ = max;
   *min_ = min;
}

int reverse(int x)
{
   int new;
   int num[32] = {0};
   int i, j;
   int ret = 0;
   int positive;
   int temp;
   int last = 0;
   int max, min;
   if (x == 0)
      return 0;
   getLimit(&max, &min);
   positive = x < 0 ? 0 : 1;
   if (!positive)
      {
         if (x == min)
            {
               return 0;
            }
         else
            x = -x;
      }
   for (i = 0; i < 32; ++i)
      {
         num[i] = x % 10;
         if (x < 10)
            break;
         x = x / 10;
      }
   j = 31;
   while (num[j] == 0)
      j--;
   if (j == 9)
      {
         if (num[0] > 2)
            return 0;
         else if (num[0] == 2)
            {
               temp = max - 2000000000;
               for (i = j; i >= 1; --i)
                  {
                     ret += num[i] * power(10, j - i);
                  }
               if (temp < ret)
                  return 0;
               ret = 0;
            }
      }
   for (i = j; i >= 0; --i)
      {
         ret += num[i] * power(10, j - i);
      }
   return positive ? ret : -ret;
}
int main()
{
   // printf("%d\n",  reverse(123));
   // printf("%d\n",  reverse(-123));
   // printf("%d\n",  reverse(120));
   // printf("%d\n",  reverse(0));
   printf("%d\n", reverse(1534236469));
}
