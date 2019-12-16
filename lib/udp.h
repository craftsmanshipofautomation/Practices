#ifndef LIB_UDP_H
#define LIB_UDP_H

#include "socket.h"

class UDPServer
{
    public:
    UDPServer(const std::string& laddr, const std::string port);
    std::string Receive();
    void Reply(const std::string &);
};



#endif
