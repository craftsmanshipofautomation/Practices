#include "libc.h"


#define CHAR_LIMIT 256

int GetState(char *pat, int M, int state, int x)
{
   if (state < M && x == pat[state])
      return state + 1;

   int ns, i;
   for (ns = state; ns > 0; ns--)
      {
         //                    [state]
         // -------------------X
         //                 ***X
         //                    [ns-1]
         if (pat[ns - 1] == x)
            {
               // length ns-1
               for (i = 0; i < ns - 1; ++i)
                  {
                     if (pat[i] != pat[state - (ns - 1) + i])
                        break;
                  }
               if (i == ns - 1)
                  return ns;
            }
      }
   return 0;
}

void ComputeTF(char *pat, int M, int TF[][CHAR_LIMIT])
{
   int state, x;
   for (state = 0; state < M + 1; ++state)
      for (x = 0; x < CHAR_LIMIT; ++x)
         TF[state][x] = GetState(pat, M, state, x);
}

void Search(char *pat, char *text)
{
   int M = strlen(pat);
   int N = strlen(text);

   int matches[100];
   int matcnt = 0;

   int TF[M + 1][CHAR_LIMIT];
   ComputeTF(pat, M, TF);

   char *curr;
   int i;
   int state;
   int input;
   for (i = 0, state = 0; i < N; ++i)
      {
         input = text[i];
         state = TF[state][input];
         if (state == M)
            {
               matches[matcnt++] = i - M + 1;
               printf("match at index %d\n", i - M + 1);
            }
      }
   printf("%s\n", text);
   int j;
   matches[matcnt] = N;
   for (j = 0; j < matches[0]; ++j)
      printf("*");
   for (i = 0; i < matcnt; ++i)
      {
         printf("^");
         for (j = matches[i]; j < matches[i + 1]; ++j)
            printf("*");
      }
   printf("\n");
}

int main()
{
   char *pat = "asdc";
   char *text = "sdfgadfgdfgsasdcfsdfgfhlkasdcadsfsadfadfasdfasdsdfsdf";
   Search(pat, text);
}