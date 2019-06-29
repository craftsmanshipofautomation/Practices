#ifndef LIB_TCP_H
#define LIB_TCP_H

#include "socket.h"

class TCPClient
{
  public:
    TCPClient(const char *host, const char *port);
    ~TCPClient();
    void Write(const char *str);
    std::string Read();

  private:
    S::Socket socket_;    
};

class TCPServer
{
  public:
    TCPServer(const char *port);
    S::Socket Accept();
    void Close();
    std::string Read();
    void Write(const char* str);
    int fd();


  private:
    LSocket listening_socket_;
};

#endif