#include "libc.h"


char *longestCommonPrefix(char **strs, int strsSize)
{
   int cnt = 0, i, j;
   char common;
   char *ret;
   if (strsSize == 0 || strs == NULL)
      goto end;
   for (i = 0; i < strsSize; ++i)
      {
         if (strs[i] == NULL)
            goto end;
      }
   for (cnt = 0;; ++cnt)
      {
         common = strs[0][cnt];
         for (i = 0; i < strsSize; ++i)
            {
               if (strs[i][cnt] == '\0' || strs[i][cnt] != common)
                  goto end;
            }
      }
end:
   ret = malloc(sizeof(char) * (cnt + 1));
   ret[cnt] = '\0';
   if (cnt)
      strncpy(ret, strs[0], cnt);
   return ret;
}

int main()
{
   char *s1 = "";
   char *input[1] = {s1};
   char *ret = longestCommonPrefix(input, 1);
   printf("%s\n", ret);
   free(ret);
}