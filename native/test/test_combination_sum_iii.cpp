#include <vector>
using std::vector;
//#include "libcxx.h"

vector<vector<int>> dfs(vector<int> nums, int start, int k, int n)
{
    if (n <= 0)
    {
        return {};
    }
    if (start > nums.size() - 1)
    {
        return {};
    }
    if (nums.size() - 1 - start + 1 < k)
    {
        return {};
    }
    if (k <= 0)
    {
        return {};
    }
    if (k == 1 && nums[k] == n)
    {
        return {{n}};
    }
    vector<vector<int>> ret;
    ret = dfs(nums, start + 1, k, n);

    for (int i = start+1; i < nums.size() - 1; ++i)
    {
        int m = n - nums[k];
        auto &&s = dfs(nums, i, k - 1, m);
        for (auto &i : s)
        {
            vector<int> r;
            r.push_back(nums[k]);
            for (auto &j: i)
            {
                r.push_back(j);
            }
            ret.push_back(r);
        }
    }
    return ret;
}

vector<vector<int>> combinationSum3(int k, int n)
{
    vector<int> nums;
    for (int i = 4; i > 0; --i)
    {
        nums.push_back(i);
    }
    return dfs(nums, 0, k, n);
}

int main()
{
    auto r = combinationSum3(2, 5);
    //for (auto &i : r)
    //    print(i);
}