#include "libcxx.h"


int main()
{
    unsigned char ip_fields[4] = {192, 168, 0, 1};
    unsigned char mask_fields[4] = {255, 255, 255, 255};

    for (int i = 0; i < 4; ++i)
    {
        unsigned char b = ip_fields[i] | (~ mask_fields[i]);
        lzlog(b, u);


    }




    

}
