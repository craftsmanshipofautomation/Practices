#include "libc.h"


void reverse(char *s, int size)
{
   int i, j;
   i = 0;
   j = size - 1;
   while (i < j)
   {
      swapc(&s[i], &s[j]);
      ++i;
      --j;
   }
   printf("%s\n", s);
}

int main()
{
   char s[8] = "abcdedf";
   char s2[9] = "abcdedfg";
   
   reverse(s, strlen(s));
   reverse(s2, strlen(s2));
   
   
   
}