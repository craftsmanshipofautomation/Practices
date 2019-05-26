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


TEST(TEST_STL, disjoint_rotate)
{
   vector<int> vec1{4, 5, 2, 3};
   auto b1 = vec1.begin();
   auto e1 = b1 + 2;
   auto b2 = b1 + 3;
   auto e2 = vec1.end();   
   disjoint_rotate(b1, e1, 2, b2, e2, 1);
   print(vec1);
}

TEST(TEST_STL, disjoint_rotate2)
{
   vector<int> vec1{7, 8, 5, 6, 1, 2, 3, 4};
   auto b1 = vec1.begin();
   auto e1 = b1 + 2;
   auto b2 = b1 + 4;
   auto e2 = vec1.end();   
   disjoint_rotate(b1, e1, 2, b2, e2, 4);
   print(vec1);
}


TEST(TEST_STL, disjoint_rotate3)
{
   vector<int> vec1{0, 1, 3 ,5, 2, 4};
   auto b1 = vec1.begin() + 3;
   auto e1 = b1 + 1;
   auto b2 = b1 + 2;
   auto e2 = vec1.end();   
   disjoint_rotate(b1, e1, 1, b2, e2, 1);
   print(vec1);
}


TEST_END