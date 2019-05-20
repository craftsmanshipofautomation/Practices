#include "libcxx.h"

using namespace std;

vector<vector<int>> permute1(vector<int> nums, int N)
{
   vector<vector<int>> ret;
   if (N == 1)
      { 
         for (auto& i : nums)
            ret.push_back(vector<int>{i});
         return ret;
      }

   for (auto i = nums.begin(); i != nums.end(); ++i)
      {

         iter_swap(i, nums.begin());
         auto lacks =
             permute1(vector<int>(nums.begin() + 1, nums.end()), N - 1);
         for (auto &j : lacks)
            {
               j.push_back(*nums.begin());
            }
         ret.insert(end(ret), begin(lacks), end(lacks));
      }

   return ret;
}

