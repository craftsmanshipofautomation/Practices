#include <gtest/gtest.h>

#define TEST_BEGIN
#define TEST_END                              \
   int main(int argc, char **argv)            \
   {                                          \
      ::testing::InitGoogleTest(&argc, argv); \
      return RUN_ALL_TESTS();                 \
   }

template <
    template <typename TT,
              typename = std::allocator<TT>> class T,
    class U>
void expect_eq(T<U> &v1, T<U> &v2)
{

   EXPECT_EQ(v1.size(), v2.size());

   typename T<U>::const_iterator b1 = v1.begin();
   typename T<U>::const_iterator b2 = v2.begin();
   while (b1 != v1.end())
   {
      EXPECT_EQ(*b1++, *b2++);
   }
}