#include "libcxx.h"

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int dir = 0; // 0 right, 1 down, 2 left, 3 up
        // next dir = curr dir + 1 % 4
        // matrix[row][column]

        vector<int> res;
        int r = 0, c = 0;
        int min_c = 0;
        int max_c = matrix[0].size();
        int min_r = 0;
        int max_r = matrix.size(); 
        int num = max_c * max_r;
        int tmp;
        while (num)
        {
            if (dir == 0)
            {
                tmp = c;
                for (; c < max_c; ++c)
                    res.push_back(matrix[r][c]);
                num -= (max_c - tmp);
                ++min_r;
                --c;
                ++r;
            }
            else if (dir == 1)
            {
                tmp = r;
                for (; r < max_r; ++r)
                {
                    res.push_back(matrix[r][c]);
                }
                num -= (max_r - tmp);
                --r;
                --c;
                --max_c;
            }
            else if (dir == 2)
            {
                tmp = c;
                for (; c >= min_c; --c)
                    res.push_back(matrix[r][c]);
                num -= (tmp - min_c + 1);
                ++c;
                --r;
                ++min_c;
            }
            else if (dir == 3)
            {
                tmp = r;
                for (; r >= min_r; --r)
                    res.push_back(matrix[r][c]);
                num -= (tmp - min_r + 1);
                ++r;
                ++c;
                --max_r;
            }
            dir = (dir + 1) % 4;
        }
        return res;



    }
};

int main()
{
    Solution s;
    vector<vector<int>> matrix = 
    {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
    };
    auto ret = s.spiralOrder(matrix);
    print(ret);
}