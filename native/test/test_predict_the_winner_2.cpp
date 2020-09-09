using namespace std;
#include "libcxx.h"

bool PredictTheWinner(vector<int>& nums) {
    int delta[20][20] = {0};
    int len = nums.size();
    for (int i = 0; i < len; ++i) {
        delta[i][i] = nums[i];
    }
    for (int i = len - 2; i >= 0; --i) {
        for (int j = i + 1; j < len; ++j)
            delta[i][j] = max(nums[i] - delta[i+1][j], nums[j] - delta[i][j-1]);
    }
    return delta[0][len - 1] > 0;

}

TEST_BEGIN

TEST(LEETCODE, PredictTheWinner)
{
    vector<int> vec = {1, 5, 233, 7};
    ASSERT_TRUE(PredictTheWinner(vec));
}


TEST_END