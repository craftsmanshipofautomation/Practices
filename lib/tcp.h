#ifndef LIB_TCP_H
#define LIB_TCP_H

#include "socket.h"

class TCPClient
{
  public:
    TCPClient(const char *host, const char *port);
    ~TCPClient();
    void Write(const char *str);
    const char *Read();

  private:
    S::Socket socket_;    
};

class TCPServer
{
  public:
    TCPServer(const char *port);
    void Accept();
    void Close();
    const char* Read();
    void Write(const char* str);

  private:
    LSocket listening_socket_;
    S::Socket conn_socket_;
};

#endif