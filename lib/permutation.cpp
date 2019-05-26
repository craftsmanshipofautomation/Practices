#include "libcxx.h"

using namespace std;

//// https://www.topcoder.com/blog/generating-permutations/

// ineffecient but easy to understand
/*
执行用时 : 24 ms, 在Permutations的C++提交中击败了60.28% 的用户
内存消耗 : 11.3 MB, 在Permutations的C++提交中击败了5.01% 的用户
*/
vector<vector<int>> PermuteR(vector<int> nums, int N)
{
   vector<vector<int>> ret;
   if (N == 1)
   {
      for (auto &i : nums)
         ret.push_back(vector<int>{i});
      return ret;
   }

   for (auto i = nums.begin(); i != nums.end(); ++i)
   {

      iter_swap(i, nums.begin());
      auto sub =
          PermuteR(vector<int>(nums.begin() + 1, nums.end()), N - 1);
      for (auto &lack1 : sub)
      {
         lack1.push_back(*nums.begin());
      }
      ret.insert(end(ret), begin(sub), end(sub));
   }

   return ret;
}

// backtrace
struct Permutation
{
   vector<vector<int>> Permute(vector<int> &nums, int N)
   {
      if ((size_t)N > nums.size() || size_t(N) == 0)
      {
         return ret_;
      }
      Permute_(nums, 0, size_t(N));
      return ret_;
   }
   vector<vector<int>> ret_;
   void Permute_(vector<int> &nums, size_t offset, size_t N)
   {
      if (offset == N)
      {
         ret_.push_back(vector<int>(nums.begin(), nums.begin() + offset));
      }

      for (auto i = offset; i < nums.size(); ++i)
      {
         swap(nums[i], nums[offset]);
         Permute_(nums, offset + 1, N);
         swap(nums[i], nums[offset]);
      }
   }
};

vector<vector<int>> Permute(vector<int> nums, int N)
{
   Permutation p;
   p.Permute(nums, N);
   return p.ret_;
}

bool NextPermutation(vector<int> &vec)
{
   // Find non-increasing suffix
   if (vec.empty())
      return false;
   vector<int>::iterator i = vec.end() - 1;
   while (i > vec.begin() && *(i - 1) >= *i)
      --i;
   if (i == vec.begin())
      return false;

   // Find successor to pivot
   vector<int>::iterator j = vec.end() - 1;
   while (*j <= *(i - 1))
      --j;
   iter_swap(i - 1, j);

   // Reverse suffix
   reverse(i, vec.end());
   return true;
}

vector<vector<int>> LexicographicalPermutatation(vector<int> nums)
{
   vector<vector<int>> ret;
   do
   {
      ret.push_back(nums);
   } while (NextPermutation(nums));
   return ret;
}
