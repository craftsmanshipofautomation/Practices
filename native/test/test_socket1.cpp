#include "libcxx.h"


int main()
{
    using namespace S;
    HostInfo hi("www.pornhub.com");
    auto addr4 = hi.GetIPv4AddrH();
    auto addr6 = hi.GetIPv6AddrH();
    print(addr4);
    print(addr6);

    auto saddr4 = hi.GetIPv4AddrS();
    auto saddr6 = hi.GetIPv6AddrS();
    print(saddr4);
    //print(saddr6);
}