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

int addup(char *start, int len)
{
   char *curr = start;
   int sum = 0;
   int i;
   for (i = len - 1; i >= 0; --i)
      {
         sum += (*curr - 48) * power(10, i);
         ++curr;
      }
   return sum;
}

int actualAtoi(char *start, char *end, int negative)
{
   int i;
   char *curr = start;
   int len = end - start;
   int critic = 0;
   int sum = 0;
   if (len > 10)
      {
         if (negative)
            return INT_MIN;
         return INT_MAX;
      }
   else if (len == 10)
      {
         if (*start > '2')
         {
            if(negative)
               return INT_MIN;
            else
               return INT_MAX;
         }
         else if (*start == '2')
            {
               critic = addup(start + 1, 9);
               if (negative)
                  {
                     if (critic > INT_MAX - 2000000000 + 1)
                        {
                           return INT_MIN;
                        }
                  }
               else
                  {
                     if (critic > INT_MAX - 2000000000)
                        {
                           return INT_MAX;
                        }
                  }
            }
      }

   if (critic)
      {
         if (negative)
            {
               sum = -1 * critic - 2000000000;
            }
         else
            sum = critic + 2000000000;
      }
   else
      {
         sum = addup(start, len);
         sum = negative ? -1 * sum : sum;
      }
   return sum;
}

int myAtoi(char *str)
{
   char *curr = str;
   char *start, *end;
   int negative = 0;
   int ret = 0;
   if (*curr == '\0')
      return 0;
   while (*curr == ' ')
      ++curr; // skip blanks
   if (*curr != '-' && *curr != '+' && !isdigit(*curr))
      return 0;
   if (*curr == '-' || *curr == '+')
      {
         if (*(curr + 1) == '\0')
            return 0;
         else if (!isdigit(*(curr + 1)))
            return 0;
         else
            {
               if (*curr == '-')
                  negative = 1;
               else
                  negative = 0;
            }
         ++curr;
      }
   while (*curr == '0') ++curr;
   start = curr;
   while (isdigit(*curr))
      ++curr;
   end = curr;
   ret = actualAtoi(start, end, negative);
   return ret;
}

int main()
{
   // printf("%d\n", myAtoi("42"));
   // printf("%d\n", myAtoi("   -42"));
   // printf("%d\n", myAtoi("4193 with words"));
   // printf("%d\n", myAtoi("words and 987"));
   // printf("%d\n", myAtoi("-91283472332"));
   //printf("%d\n", myAtoi("+1"));
   //printf("%d\n", myAtoi("  0000000000012345678"));
   printf("%d\n", myAtoi("-6147483648"));


}