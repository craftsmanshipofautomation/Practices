#include "libc.h"


void swap(int *i, int *j)
{
   int temp = *i; *i = *j; *j = temp;
}

void swapc(char *i, char *j)
{
   char temp = *i; *i = *j; *j = temp;   
}

int number_span_positive(int n)
{
   int i = 1;
   while (n > 9)
   {
      n = n / 10;
      ++i;
   }
   return i;
}
int number_span(int n)
{
   if (n > INT_MAX || n < INT_MIN)
      return 0;
   if (n == INT_MIN)
      n = INT_MIN + 1;
   if (n < 0)
      return number_span_positive(n * -1) + 1;
   else
      return number_span_positive(n);
}



void arrncpy(int *dest, int *src, int size)
{
   // dangerous
   int i;
   for (i = 0; i < size; ++i)
   {
      dest[i] = src[i];
   }
}

void copychars(char *dest, char *src, int size)
{
   // dangerous
   int i;
   for (i = 0; i < size; ++i)
   {
      dest[i] = src[i];
   }
}
