#include "tcp.h"

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

const char *TCPClient::Read() 
{ 
    socket_.Read();
    return socket_.str();
}

TCPServer::TCPServer(const char *port)
: listening_socket_(Open_listenfd(const_cast<char*>(port)))
{}

void TCPServer::Accept() 
{ 
    conn_socket_ = listening_socket_.Accept(); 
}

const char *TCPServer::Read() 
{
    conn_socket_.Read();
    return conn_socket_.str();
}

void TCPServer::Write(const char* str)
{ 
    conn_socket_.Write(str); 
}
