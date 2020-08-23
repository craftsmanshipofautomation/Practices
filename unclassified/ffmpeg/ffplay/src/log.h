#ifndef L744D6CBC_0134_1397_147C_D54F21B72566
#define L744D6CBC_0134_1397_147C_D54F21B72566

#ifdef LOGF
#undef LOGF
#endif

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

#define LOGF(...) logging(_##_FILE__, _##_LINE__, _##_FUNCTION__, __VA_ARGS__)

inline void logging(const char *file, int line, const char *function,
                    const char *fmt, ...);

#define ELEVENTH_ARGUMENT(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, ...) a11
#define COUNT_ARGUMENTS(...)                                                   \
   ELEVENTH_ARGUMENT(dummy, ##__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

static void _lzlog(const char *str, const char *type, char *fmt)
{
   va_list args;
   va_list vl;
   char type_char = type[0];
   snprintf(fmt, 256, "%s: %%%c", str, type_char);
}
#define lzlog(EXPR, TYPE)                                                      \
   do                                                                          \
      {                                                                        \
         char _fmt[256];                                                       \
         _lzlog(#EXPR, #TYPE, _fmt);                                           \
         /*fprintf(stdout, "%s", _fmt);*/                                      \
         /*fprintf(stdout, "\n");*/                                            \
         fprintf(stdout, Yellow);                                              \
         fprintf(stdout, "%s:%d ", _##_FILE__, _##_LINE__);                    \
         fprintf(stdout, Reset);                                               \
         fprintf(stdout, Cyan);                                                \
         fprintf(stdout, " (%s:%d): ", _##_FUNCTION__, _##_LINE__);            \
         fprintf(stdout, Reset);                                               \
         fprintf(stdout, _fmt, EXPR);                                          \
         fprintf(stdout, "\n");                                                \
      }                                                                        \
   while (0)

#define LZLOG lzlog
#define lzline() lzlog(_##_LINE__, d)

#define Zero(name) name##(##0##)

void logging(const char *file, int line, const char *function, const char *fmt,
             ...)
{
   va_list args;
   fprintf(stdout, Yellow);
   fprintf(stdout, "%s:%d ", file, line);
   fprintf(stdout, Reset);
   fprintf(stdout, Cyan);
   fprintf(stdout, " (%s:%d): ", function, line);
   fprintf(stdout, Reset);
   va_start(args, fmt);
   vfprintf(stdout, fmt, args);
   va_end(args);
   fprintf(stdout, "\n");
}

#endif /* 744D6CBC_0134_1397_147C_D54F21B72566 */
