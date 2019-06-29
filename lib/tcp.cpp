#include "tcp.h"
#include <utility>

TCPClient::TCPClient(const char *host, const char *port)
    : socket_(Open_clientfd(const_cast<char*>(host), const_cast<char*>(port)))
{
}

TCPClient::~TCPClient()
{
    
}

void TCPClient::Write(const char *str)
{ 
    socket_.Write(str);
}

std::string TCPClient::Read() 
{ 
    socket_.Read();
    return socket_.str();
}

TCPServer::TCPServer(const char *port)
: listening_socket_(Open_listenfd(const_cast<char*>(port)))
{}

S::Socket TCPServer::Accept() 
{ 
    return std::forward<S::Socket>(listening_socket_.Accept()); 
}

void TCPServer::Close()
{
    listening_socket_.Close();
}

int TCPServer::fd()
{
    return listening_socket_.fd();
}