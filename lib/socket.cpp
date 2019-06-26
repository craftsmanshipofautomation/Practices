#include "socket.h"

TCPClient::TCPClient(char *host, char *port)
    : client_fd_(Open_clientfd(host, port))
{
    Rio_readinitb(&rio_, client_fd_);
}

TCPClient::~TCPClient() { Close(client_fd_); }

void TCPClient::Write(const std::string &str)
{
    int length = str.size() > MAXLINE ? MAXLINE : str.size();
    strncpy(buf_, str.c_str(), length);
    Rio_writen(client_fd_, buf_, length);
}

const char *TCPClient::Read()
{
    Rio_readlineb(&rio_, buf_, MAXLINE);
    return buf_;
}

TCPServer::TCPServer(char* port)
:listenfd_(Open_listenfd(port))
, clientlen_(sizeof(struct sockaddr_storage))
{
   
}


