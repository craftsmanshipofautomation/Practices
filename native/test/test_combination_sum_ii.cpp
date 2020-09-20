#include "libcxx.h"
#include <queue>
using std::queue;

vector<queue<int>> dfs(vector<int> &candidates, int start, int target)
{
    int len = candidates.size();
    if (target < 0)
    {
        return {};
    }
    if (start > len - 1)
    {
        return {};
    }
    if (candidates[start] > target)
    {
        return {};
    }
    if (candidates[start] == target)
    {
        queue<int> q;
        q.push(target);
        return {q};
    }
    auto r1 = dfs(candidates, start + 1, target);
    auto r2 = dfs(candidates, start + 1, target - candidates[start]);
    vector<queue<int>> ret;
    for (auto &r : r1)
    {
        ret.push_back(r);
    }
    for (auto &r : r2)
    {
        r.push(candidates[start]);
        ret.push_back(r);
    }
    return ret;
}
vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
{
    vector<vector<int>> r;
    int len = candidates.size();
    for (int start = 0; start < len; ++start)
    {
        auto &&s = dfs(candidates, start, target);
        for (auto &i : s)
        {
            vector<int> v;
            while (!i.empty())
            {
                v.push_back(i.front());
                i.pop();
            }
            r.push_back(v);
            for (auto &i : r)
                print(i);
        }
    }
    return r;
}

int main()
{
    vector<int> a = {10, 1, 2, 7, 6, 1, 5};
    auto r = combinationSum2(a, 8);
    for (auto &i : r)
        print(i);
}