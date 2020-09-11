#include "libcxx.h"
#include "udp.h"


int main()
{
    try
    {
        UDPServer svr("10.2.3.1", "2323");
        svr.Run();
    }
    catch (Error& e)
    {
        lzlog(e.what(), s);
    }
}