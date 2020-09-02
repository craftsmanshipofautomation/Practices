using namespace std;
#include "libcxx.h"


bool _a(vector<int>& nums, int head, int tail, int turn, int* score) {
    if (tail == head) {
        score[turn] += nums[head];
        if (score[0] >= score[1])
            return true;
        return false;
    } else {
        int s0 = score[0];
        int s1 = score[1];
        score[turn] += nums[head];
        if (_a(nums, head+1, tail, (turn+1)%2, score)) {
            if (turn == 0) {
                return true;
            }
        } else {
            if (turn == 1) {
                return false;
            }
        }
        score[0] = s0;
        score[1] = s1;
        score[turn] += nums[tail];
        return _a(nums, head, tail-1, (turn+1)%2, score);
    }
}

bool PredictTheWinner(vector<int>& nums) {
    int head = 0, tail = nums.size() - 1;
    int turn = 0;
    int score[2] = {0};
    return _a(nums, head, tail, turn, score);
}


TEST_BEGIN

TEST(LEETCODE, PredictTheWinner)
{
    vector<int> vec = {1, 5, 233, 7};
    ASSERT_TRUE(PredictTheWinner(vec));
}


TEST_END

