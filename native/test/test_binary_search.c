#include "libc.h"
extern int arr[1000];

int main()
{
   int r = binary_search(arr, 1000, 1000);
   lzlog(r, d);
}


#include "test_data.dat"