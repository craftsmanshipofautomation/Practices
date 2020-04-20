#include "libc.h"
/*
304 / 304 个通过测试用例
	状态：通过
执行用时：8 ms
*/

double myPow_(double x, int n){
    if (n == 0)
        return 1.0;
    double temp = myPow_(x, n/2);
    if (n % 2)
        return temp * temp * x;
    else
        return temp * temp;
}

double myPow(double x, int n)
{
    int n_ = n;
    double extra = 1.0;
    if (n == INT_MIN)
    {
        n_ = INT_MAX;
        extra = 1 / x;
    }
    double res = myPow_(x, n_);
    if (n < 0)
        res = 1.0 / res;
    return res * extra;
}

int main()
{
    
}