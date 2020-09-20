#include "libc.h"

void test_native_matching()
{
   
   printf("--- native string matching ---\n");
   const char* text = "babababababa";
   const char* pat = "ab";
   int rz;
   int *ret = native_pattern_search(text, pat, &rz);
   lzlog(rz, d);
   PRINT(ret, ret, rz);
   free(ret);
   
}


int main()
{
   test_native_matching();
   
}