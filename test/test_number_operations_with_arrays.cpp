#include "libcxx.h"
using namespace std;

vector<int> add(const vector<int>& lhs, const vector<int>& rhs, int base)
{
   int lsize = lhs.size();
   int rsize = rhs.size();   
   int max_size = max(lsize, rsize) + 1;
   vector<int> ret(max_size, 0);   
   
   int temp, i = 0, left, right;
   while (!(i >= lsize && i >= rsize))
   {
      left = 0; right = 0;
      if (i < lsize) left = lhs[i];
      if (i < rsize) right = rhs[i];
      temp = left + right + ret[i];
      if (temp >= base)
      {
         ret[i] = temp % base;
         ret[i+1] = temp / base;
      }
      else
         ret[i] = temp % base;
      ++i;
   }
   auto tail = ret.cend();
   while (*--tail == 0) ret.pop_back();
   return ret;
}

TEST_BEGIN

// arabian style of writing

TEST(SIMULATION, add2)
{
   vector<int> lhs      {1, 0, 1};
   vector<int> rhs      {1, 0, 1};
   vector<int> expected {0, 1, 0, 1};   
   vector<int> r = add(lhs, rhs, 2);
   expect_eq(expected, r);
}

TEST(SIMULATION, add10)
{
   vector<int> lhs      {2, 0, 1};
   vector<int> rhs      {8, 9, 1};
   vector<int> expected {0, 0, 3};   
   vector<int> r = add(lhs, rhs, 10);
   expect_eq(expected, r);
}


TEST_END