#include "libcxx.h"
#include <gtest/gtest.h>


TEST_BEGIN

TEST(TEST_STL, rotation)
{
   vector<int> vec1{1, 2, 3, 4, 5};
   using std::rotate;
   auto first = vec1.begin();
   auto last = vec1.end();   
   auto mid = first + 1;
   rotate(first, mid, last);
   print(vec1);
}

TEST(TEST_STL, rotation2)
{
   vector<int> vec1{1, 2, 3, 4, 5};
   using std::rotate;
   auto first = vec1.begin()+1;
   auto last = vec1.end();   
   auto mid = first + 1;
   rotate(first, mid, last);
   print(vec1);
}

TEST(TEST_STL, first_iterator_minus_one_is_less_than_the_first)
{
   vector<int> vec{1, 2, 3, 4, 5};   
   auto first = vec.begin();
   auto i = first;
   --i;
   ASSERT_TRUE(i < first);
}

TEST(TEST_STL, yarotation)
{
   vector<int> vec1{1, 2, 3, 4, 5, 6, 7};
   auto first = vec1.begin();
   auto last = vec1.end();   
   auto next_first = first + 3;
   ya_rotate(first, next_first, last);
   print(vec1);
}

TEST(TEST_STL, yarotation2)
{
   vector<int> vec1{4, 5, 3};
   auto first = vec1.begin();
   auto last = vec1.end();   
   auto next_first = first + 2;
   ya_rotate(first, next_first, last);
   print(vec1);
}


TEST_END