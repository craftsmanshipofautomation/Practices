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
  void Close();
  int fd() { return fd_; }
  std::string str();
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
    void Close();
    int fd() { return lfd_; }
    S::Socket Accept();

  private:
    int lfd_;
    struct sockaddr_storage clientaddr_;
    socklen_t clientlen_;
    char client_hostname_[MAXLINE];
    char client_port_[MAXLINE];
};



class UDPSocket
{
  public:
  // to initialize is to bind
  UDPSocket(const std::string& addr, const std::string& port);
  std::string Receive();
  std::string GetRemoteAddr();
  int GetRemotePort();
  void Reply(const std::string&);
  static constexpr int bufsize() { return 2048; }

  private:
  struct sockaddr_in my_addr_;
  struct sockaddr_in remote_addr_;
  int fd_of_this_socket_;
  socklen_t addrlen_;
  unsigned char buf_[UDPSocket::bufsize()];

};

namespace S
{
// socket utils
void set_address(const char *host, const char *port, struct sockaddr_in *sap, char* protocol);

class SockAddr
{
  public:
  SockAddr(const std::string &host, const std::string& service);
  
  private:
  struct sockaddr general_addr_;
  struct sockaddr_in ipv4_addr_;
  
  
};


}

// todo: 
//  1. rename socket to tcp socket
//  ~~2. add udp socket~~
#endif