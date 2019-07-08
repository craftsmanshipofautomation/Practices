#ifndef FTF_H
#define FTF_H
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define escape \033

#define Red "\033[0;31m"
#define Bold_Red "\033[1;31m"
#define Green "\033[0;32m"
#define Bold_Green "\033[1;32m"
#define Yellow "\033[0;33m"
#define Bold_Yellow "\033[01;33m"
#define Blue "\033[0;34m"
#define Bold_Blue "\033[1;34m"
#define Magenta "\033[0;35m"
#define Bold_Magenta "\033[1;35m"
#define Cyan "\033[0;36m"
#define Bold_Cyan "\033[1;36m"
#define Reset "\033[0m"

//static void _lzlog(const char *str, const char *type, char *fmt)
//{
//   char type_char = type[0];
//   snprintf(fmt, 256, "%s: %%%c", str, type_char);
//}

#define lzlog(EXPR, TYPE)                                        \
   do                                                            \
   {                                                             \
      char _fmt[256];                                            \
      char type_char = #TYPE[0];                                 \
      snprintf(_fmt, 256, "%s: %%%c", #EXPR, type_char);         \
      /*fprintf(stdout, "%s", _fmt);*/                           \
      /*fprintf(stdout, "\n");*/                                 \
      fprintf(stdout, Yellow);                                   \
      fprintf(stdout, "%s:%d ", _##_FILE__, _##_LINE__);         \
      fprintf(stdout, Reset);                                    \
      fprintf(stdout, Cyan);                                     \
      fprintf(stdout, " (%s:%d): ", _##_FUNCTION__, _##_LINE__); \
      fprintf(stdout, Reset);                                    \
      fprintf(stdout, _fmt, EXPR);                               \
      fprintf(stdout, "\n");                                     \
   } while (0)

#define PRINT(name, arr, size)    \
   {                              \
      printf("%s: [ ", #name);    \
      int i;                      \
      for (i = 0; i < size; ++i)  \
      {                           \
         printf("%d ", (arr)[i]); \
      }                           \
      printf("]\n");              \
   }

#define PRINTF(name, arr, size)    \
   {                              \
      printf("%s: [ ", #name);    \
      int i;                      \
      for (i = 0; i < size; ++i)  \
      {                           \
         printf("%f ", (arr)[i]); \
      }                           \
      printf("]\n");              \
   }

#define PRINTC(name, arr, size)   \
   {                              \
      printf("%s: [ ", #name);    \
      int i;                      \
      for (i = 0; i < size; ++i)  \
      {                           \
         printf("%d ", (arr)[i]); \
      }                           \
      printf("]\n");              \
   }

#endif