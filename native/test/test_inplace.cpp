#include "libcxx.h"

namespace
{

// 空间复杂度 O(1)
// 时间复杂度 O(N/2)
void reverse(int *A, int head, int tail)
{
    while (head < tail)
    {
        swap(A[head++], A[tail--]);
    }
}

void rotate(int *A, int s1, int s2, int end)
{
    reverse(A, s1, s2-1);
    reverse(A, s2, end);
    reverse(A, s1, end);
}

void merge(int *A, int s1, int s2, int end)
{
    int tmp = 0;
    while (s2 < end)
    {
        while (A[s1] < A[s2])
            ++s1;
        tmp = s2;
        while (A[s2] < A[s1])
            ++s2;
        rotate(A, s1, tmp, s2-1);
    }
}

} // namespace

int main()
{
    int A[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int B[10] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    ::reverse(A, 0, 9);
    print(A, (size_t)10);
    ::rotate(A, 0, 5, 9);
    print(A, (size_t)10);
    merge(B, 0, 5, 9);
    print(B, (size_t)10);
}