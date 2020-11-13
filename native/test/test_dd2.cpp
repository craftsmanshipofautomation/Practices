#include "libcxx.h"

// 1 4 5
//
int max_(vector<int> &arr)
{
    int left = 0, right = arr.size() - 1;

    while (1)
    {
        if (left == right) // 1
            break;
        if (right - left == 1) // 2
        {
            left = arr[right] > arr[left] ? right : left;
            break;
        }
        int mid = (left + right) / 2;
        if (arr[mid - 1] < arr[mid] && arr[mid + 1] < arr[mid])
        {
            left = mid;
            break;
        }
        else if (arr[mid + 1] > arr[mid - 1])
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return arr[left];
}

int main()
{
    vector<int> arr = {10, 9, 8};
    lzlog(max_(arr), d);
}