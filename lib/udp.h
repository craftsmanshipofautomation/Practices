#ifndef LIB_UDP_H
#define LIB_UDP_H

#include "socket.h"

class UDPServer
{
    public:
    UDPServer(const std::string& laddr, const std::string port);
    virtual void Run();

    private:
    UDPSocket socket_;
};



#endif
