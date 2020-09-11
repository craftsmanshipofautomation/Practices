#include "libcxx.h"
#include <string>

using namespace std;

TEST_BEGIN

TEST(TEST_ENCODING, alpha)
{
   string str = "α";
   string encoded;
   char out[2];
   for (auto& c : str)
   {
      if (base64_encode(c, out))
      {
         encoded += '%';
         encoded += out[0];
         encoded += out[1];         
      }
      else
         encoded += c;
   }
   EXPECT_EQ(encoded, "%CE%B1");
     
}

TEST(TEST_ENCODING, du)
{
   string str = "读";
   string encoded;
   char out[2];
   for (auto& c : str)
   {
      if (base64_encode(c, out))
      {
         encoded += '%';
         encoded += out[0];
         encoded += out[1];         
      }
      else
         encoded += c;
   }
   EXPECT_EQ(encoded, "%E8%AF%BB");
     
}

TEST(TEST_ENCODING, it_is_no_test)
{
   // generate test source
   uchar end = 254;
   for (uchar uc = 32; uc <= end; uc = uc + 1)
   {
      printf("## %u%c%c%c\n", uc, 'a', uc, 'b');
   }
     
}

TEST_END