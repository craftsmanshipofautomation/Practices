#include "libcxx.h"

namespace S
{
    
Socket::Socket(): buf_(nullptr) {}

Socket::Socket(int fd) :
fd_(fd), buf_(new char[MAXLINE])
, rio_(new rio_t())
{
    Rio_readinitb(rio_, fd_);
}

void Socket::Move(Socket& dest, Socket& src)
{
    dest.rio_ = src.rio_;
    dest.buf_ = src.buf_;
    dest.fd_ = src.fd_;
    dest.bufsize_ = src.bufsize_;
    src.rio_ = nullptr;
    src.buf_ = nullptr;
    src.fd_ = -1;
}

Socket::Socket(Socket&& socket)
{
    Socket::Move(*this, socket);
    Rio_readinitb(rio_, fd_);    
}

Socket& Socket::operator=(Socket &&socket)
{
    Socket::Move(*this, socket);
    Rio_readinitb(rio_, fd_);            
}

Socket::~Socket() 
{ 
    if (fd_ != -1)
        ::Close(fd_);
    if (buf_)
        delete[] buf_;
    if (rio_)
        delete rio_;
}
void Socket::Close()
{
    ::Close(fd_);
    fd_ = -1;
}
size_t Socket::Write(const char* str)
{
    int len = strlen(str);
    if (len > MAXLINE)
        len = MAXLINE;
    strncpy(buf_, str, len);
    Rio_writen(fd_, buf_, len);
    return len;
}

size_t Socket::Read()
{
    Rio_readinitb(rio_, fd_);    
    bufsize_ = Rio_readlineb(rio_, buf_, MAXLINE); // including '\n'
    return bufsize_;
}

std::string Socket::str()
{
    if (bufsize_ > 0)
        buf_[bufsize_-1] = '\0';
    return std::string(buf_);
}


// to fill sap
void set_address(char *host, char *service, struct sockaddr_in *sap, char* protocol)
{
    struct servent *sp;
    struct hostent *hp;
    char *endptr;
    short port;
    
    memset(sap, 0, sizeof(sap));
    sap->sin_family = AF_INET;
    if (host != NULL)
    {
        if (!inet_aton(host, &sap->sin_addr))
        {
            hp = gethostbyname(host);
            if (hp == NULL)
                throw Error("gethostbyname");
            sap->sin_addr = *(struct in_addr*)hp->h_addr;
        }
    }
    else
    {
        sap->sin_addr.s_addr = htonl(INADDR_ANY);
    }
    port = strtol(service, &endptr, 0);
    // if this is not the end of it
    if (*endptr == '\0')
    {
        sap->sin_port = htons(port);
    }
    else
    {
        sp = getservbyname(service, protocol);
        if (sp == NULL)
        {
            throw Error("Unknown service");
        }
        sap->sin_port = sp->s_port;
    }
    
}

} // namespace S

LSocket::LSocket(int fd) : lfd_(fd), clientlen_(sizeof(struct sockaddr_storage))
{
    int yes = 1;
    setsockopt(lfd_, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
}
void LSocket::Close()
{
    ::Close(lfd_);
    lfd_ = -1;
}
LSocket::~LSocket()
{
    if (lfd_ != -1)
        ::Close(lfd_);
}

S::Socket LSocket::Accept()
{
    int connfd = ::Accept(lfd_, (SA *)&clientaddr_, &clientlen_);
    S::Socket ret(connfd);
    Getnameinfo((SA *)&clientaddr_, clientlen_, client_hostname_, MAXLINE,
                client_port_, MAXLINE, 0);
    return std::move(ret);
}

UDPSocket::UDPSocket(const std::string& addr, const std::string& port)
{
    fd_of_this_socket_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd_of_this_socket_)
    {
        throw Error("creation of data gram socket");
    }
    memset(&my_addr_, 0, sizeof(my_addr_));
    //S::set_address(addr.c_str(), port.c_str(), &my_addr_, "udp");
    //::Bind(fd_of_this_socket_, (struct sockaddr *)&my_addr_, sizeof(my_addr_));
    //addrlen_ = (socklen_t)sizeof(remote_addr_);
}

std::string UDPSocket::Receive()
{
    int recvlen = recvfrom(fd_of_this_socket_, buf_, UDPSocket::bufsize(), 0, \
        (struct sockaddr*)&remote_addr_, &addrlen_);
        
    return "";
}

std::string UDPSocket::GetRemoteAddr()
{
    //return remote_addr_.sin_addr
 return  "";   
    
}

int UDPSocket::GetRemotePort()
{
 return  0;   
}

namespace S
{

HostInfo::HostInfo(const std::string& website)
: valid_(true)
{
    struct addrinfo hints, *res, *p;
    int status;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    if ((status = getaddrinfo(website.c_str(), NULL, &hints, &res)) != 0)
    {
        valid_ = false;
    }
    for (p = res; p != NULL; p = p->ai_next)
    {
        void *addr;
        if (p->ai_family == AF_INET)
        {
            struct sockaddr_in s4;
            struct sockaddr_in *ipv4 = (struct sockaddr_in*)p->ai_addr;
            addr = &(ipv4->sin_addr);
            inet_ntop(p->ai_family, addr, ipstr_, sizeof ipstr_);
            ipv4_addrs_.push_back(ipstr_);
            memcpy(&s4, ipv4, sizeof(struct sockaddr_in));
            sockaddrs4_.push_back(std::move(s4));
        }
        else
        {
            struct sockaddr_in6 s6;
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            inet_ntop(p->ai_family, addr, ipstr_, sizeof ipstr_);
            ipv6_addrs_.push_back(ipstr_);
            memcpy(&s6, ipv6, sizeof(struct sockaddr_in6));
            sockaddrs6_.push_back(std::move(s6));
        }

    }
    freeaddrinfo(res);

}

std::vector<std::string>& HostInfo::GetIPv4AddrH()
{
    return ipv4_addrs_;
}

std::vector<std::string>& HostInfo::GetIPv6AddrH()
{
    return ipv6_addrs_;
}

std::vector<struct sockaddr_in>& HostInfo::GetIPv4AddrS()
{
    return sockaddrs4_;
}
  std::vector<struct sockaddr_in6>& HostInfo::GetIPv6AddrS()
{
    return sockaddrs6_;

}

void print(struct sockaddr_in *si)
{
    lzlog(si->sin_family, hu);
    lzlog(si->sin_port, hu);
    //print_inaddr(&(si->sin_addr.s_addr));
}

void print_inaddr(struct in_addr* inaddr)
{
    char *p = (char*)&inaddr;
    int i = 0;
    for (;i < sizeof(struct in_addr); ++i, ++p)
    {
        printf("%c, ", *p);
    }
    printf("\n");

}



}


