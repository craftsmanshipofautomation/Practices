#ifndef LIB_SOCKET_H
#define LIB_SOCKET_H
#include "csapp.h"
#include <string>
#include <memory>

namespace S
{
class Socket
{
  public:
  Socket();
  Socket(int fd);
  Socket(Socket&&);  
  Socket & operator=(Socket &&);  
  ~Socket();
  size_t Write(const char* str);
  size_t Read();
  int fd() { return fd_; }
  const char* str();
  private:
  Socket(const Socket &) = delete;
  static void Move(Socket& dest, Socket& src);
  private:
    int fd_;
    rio_t* rio_;
    char* buf_;
    int bufsize_;
};
}

// listening socket
class LSocket
{
  public:
    LSocket(int fd);
    ~LSocket();
    S::Socket Accept();

  private:
    int lfd_;
    struct sockaddr_storage clientaddr_;
    socklen_t clientlen_;
    char client_hostname_[MAXLINE];
    char client_port_[MAXLINE];
};


#endif