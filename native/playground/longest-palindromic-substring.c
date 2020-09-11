#include "libc.h"

#define MAX(x, y) ((x) > (y)) ? (x) : (y)
#define MIN(x, y) ((x) < (y)) ? (x) : (y)

char *longestPalindrome(char *s)
{
   int str_len = strlen(s);
   char *ret;
   int len;

   int cs, ce, curr;
   int max_l = 1;
   int r;
   int start = 0;
   int error = 0;

   for (len = str_len; len > 1; --len)
   {
      if (len % 2)
      {
         cs = (len - 1) / 2;
         ce = str_len - 1 - (len - 1) / 2;
         for (curr = cs; curr <= ce; ++curr)
         {
            error = 0;
            for (r = 1; r <= len / 2; ++r)
            {
               if (s[curr - r] != s[curr + r])
               {
                  error = 1;
                  break;
               }
            }
            if (!error)
            {
               max_l = len;
               start = curr - len/2;
               goto end;
            }
         }
      }
      else
      {
         cs = len / 2 - 1;
         ce = str_len - len / 2 - 1;
         for (curr = cs; curr <= ce; ++curr)
         {
            error = 0;
            for (r = 1; r <= len / 2; ++r)
            {
               if (s[curr + 1 - r] != s[curr + r])
               {
                  error = 1;
                  break;
               }
            }
            if (!error)
            {
               max_l = len;
               start = curr - len/2 + 1;
               goto end;
            }
         }
      }
   }

end:
   printf("strlen: %d, maxlen: %d\n", str_len, max_l);
   ret = malloc(sizeof(char) * (max_l + 1));
   ret[max_l] = '\0';
   strncpy(ret, s + start, max_l);
   return ret;
}

void test(char *s)
{
   printf("=======================================\n");
   printf("test for %s\n", s);
   printf("=======================================\n");
   char *res = longestPalindrome(s);
   printf("result: %s\n", res);
   free(res);
}

int main()
{
   char *s0 = "";
   char *s1 = "a";
   char *s2 = "aa";
   char *s3 = "aaa";
   char *s4 = "aaaa";
   char *s5 = "abcsdscbd";
   char *s6 =
       "kyyrjtdplseovzwjkykrjwhxquwxsfsorjiumvxjhjmgeueafubtonhlerrgsgohfosqssm"
       "izcuqryqomsipovhhodpfyudtusjhonlqabhxfahfcjqxyckycstcqwxvicwkjeuboerkmj"
       "shfgiglceycmycadpnvoeaurqatesivajoqdilynbcihnidbizwkuaoegmytopzdmvvoewv"
       "hebqzskseeubnretjgnmyjwwgcooytfojeuzcuyhsznbcaiqpwcyusyyywqmmvqzvvceyln"
       "uwcbxybhqpvjumzomnabrjgcfaabqmiotlfojnyuolostmtacbwmwlqdfkbfikusuqtupdw"
       "drjwqmuudbcvtpieiwteqbeyfyqejglmxofdjksqmzeugwvuniaxdrunyunnqpbnfbgqemv"
       "amaxuhjbyzqmhalrprhnindrkbopwbwsjeqrmyqipnqvjqzpjalqyfvaavyhytetllzupxj"
       "wozdfpmjhjlrnitnjgapzrakcqahaqetwllaaiadalmxgvpawqpgecojxfvcgxsbrldktuf"
       "drogkogbltcezflyctklpqrjymqzyzmtlssnavzcquytcskcnjzzrytsvawkavzboncxlhq"
       "fiofuohehaygxidxsofhmhzygklliovnwqbwwiiyarxtoihvjkdrzqsnmhdtdlpckuayhtf"
       "yirnhkrhbrwkdymjrjklonyggqnxhfvtkqxoicakzsxmgczpwhpkzcntkcwhkdkxvfnjbvj"
       "joumczjyvdgkfukfuldolqnauvoyhoheoqvpwoisniv";
   char *s7 =
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "abcaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaa";
   char *s8 = "acbbd";
   char *s9 = "ac";
   // test(s0);
   // test(s1);
   // test(s2);
   test(s9);
}