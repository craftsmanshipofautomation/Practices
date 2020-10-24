#include "libcxx.h"


// 空间复杂度 O(1)
// 时间复杂度 O(N/2)
void reverse(int *A, size_t sz)
{
    size_t head = 0, tail = sz - 1;
    while (head < tail)
    {
        swap(A[head++], A[tail--]);
    }
}







int main()
{
    int A[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    //int A[10] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    reverse(A, 10);
    print(A, (size_t)10);
}