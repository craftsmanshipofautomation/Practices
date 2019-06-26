#ifndef LIB_SOCKET_H
#define LIB_SOCKET_H
#include <string>
#include "csapp.h"

class TCPClient
{
  public:
    TCPClient(char *host, char *port);
    ~TCPClient();
    void Write(const std::string &str);
    const char *Read();

  private:
    int client_fd_;
    riot_t rio_;
    char buf_[MAXLINE];
};


class TCPServer
{
    public:
    TCPServer(char* port);
    
    
    private:
    struct sockaddr_storage clientaddr_; 
    int listenfd_;
    int connfd_;
    int clientlen_;
    char client_hostname[MAXLINE];
    char client_port[MAXLINE];
};


#endif