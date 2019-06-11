#include "libc.h"

int* native_pattern_search(const char* text, const char* pat, int *ret_size)
{

   int text_size = strlen(text);
   int pat_size = strlen(pat);
   int i, j, k;
   int *ret = NULL;
   int result[text_size];
   int r = 0;
   for (i = 0; i < text_size - pat_size + 1; ++i)
   {
      for (j = 0, k = i; j < pat_size; ++j, ++k)
      {
         if (text[k] != pat[j])
         {
            break;
         }
      }
      if (j == pat_size)
      {
         result[r++] = i;
         
      }
         
   }
   if (r)
   {
      ret = malloc(sizeof(int) * r);
      arrncpy(ret, result, r);
   }
   *ret_size = r;   
   return ret;
}