#include "libc.h"



char * lcs(char *a, char *b)
{
   int alen = strlen(a);
   int blen = strlen(b);

   int L[alen+1][blen+1];
   int i, j, result = 0, ri = 0, rj = 0;
   for (i = 0; i < alen+1; ++i)
   {
      for (j = 0; j < blen+1; ++j)
      {
         L[i][j] = 0;
      }
   }
   for (i = 1; i < alen+1; ++i)
   {
      for (j = 1; j < blen+1; ++j)
      {
         if (a[i] == a[j])
         {
            L[i][j] = 1 + L[i-1][j-1];
            result = L[i][j];
            ri = i;
            rj = j;
         }
         else
         {
            if (L[i-1][j] > L[i][j-1])
            {
               result = L[i-1][j];
               ri = i - 1;
               rj = j;
            }
            else
            {
               result = L[i][j-1];
               ri = i;
               rj = j-1;
            }
         }
      }
   }

   return "a";

}

int main()
{
   char *r = lcs("agcsdfgdsadfa", "asdfasfasdf");
   //free(r);
}