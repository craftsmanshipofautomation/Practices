#include "libcxx.h"
#include "udp.h"

UDPServer::UDPServer(const std::string& laddr, const std::string port)
: socket_(laddr, port)
{

}

void UDPServer::Run()
{
    std::cout << "udp server running..." << std::endl;
    while(true)
    {
        std::string recv = socket_.Receive();
        std::string reply = "you said: ";
        socket_.Reply(reply + recv);
    }
}