#ifndef LIB_SOCKET_H
#define LIB_SOCKET_H
#include "libcxx.h"

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

// socket utils
void set_address(const char *host, const char *port, struct sockaddr_in *sap, const char* protocol);

class HostInfo
{
  public:
  HostInfo(const std::string& website);
  std::vector<std::string>& GetIPv4AddrH();
  std::vector<std::string>& GetIPv6AddrH();
  std::vector<struct sockaddr_in>& GetIPv4AddrS();
  std::vector<struct sockaddr_in6>& GetIPv6AddrS();

  private:
  bool IsValid() { return valid_;}
  bool valid_;
  char ipstr_[INET6_ADDRSTRLEN];
  std::vector<std::string> ipv4_addrs_;
  std::vector<std::string> ipv6_addrs_;
  std::vector<struct sockaddr_in> sockaddrs4_;
  std::vector<struct sockaddr_in6> sockaddrs6_;

};


// switch from human readable data to library data
// this is to reveal ugliness
class SockH2K
{
  public:
  SockH2K(const std::string &host, const std::string& service);
  struct sockaddr* GetGeneralLibAddr();
  struct sockaddr_in* GetIPv4LibAddr();



  private:
  // use sockaddr* to refer to 2 kinds of address
  struct sockaddr general_addr_;
  struct sockaddr_in ipv4_addr_;

};

// from library to human
class SockK2H
{
  public:
  SockK2H();

};


} // namespace S

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

// fixme
#define UDPBUFSIZE 2048
class UDPSocket
{
  public:
  // to initialize is to bind
  UDPSocket(const std::string& addr, const std::string& port);
  ~UDPSocket();
  std::string Receive();
  std::string GetLastRemoteIP();
  int GetLastRemotePort();
  void Reply(const std::string&);
  static constexpr int bufsize() { return UDPBUFSIZE; }

  private:
  struct sockaddr_in my_addr_;
  struct sockaddr_in remote_addr_;
  socklen_t addrlen_;
  std::string lastword_;
  std::string last_clntip_;
  int last_clntport_;
  int fd_of_this_socket_;
  char buf_[UDPBUFSIZE];

};

std::ostream& operator<< (std::ostream&os, struct sockaddr_in si);


// todo: 
//  1. rename socket to tcp socket
//  ~~2. add udp socket~~
#endif