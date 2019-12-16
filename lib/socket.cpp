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
    S::set_address(addr.c_str(), port.c_str(), &my_addr_, "udp");
    ::Bind(fd_of_this_socket_, (struct sockaddr *)&my_addr_, sizeof(my_addr_));
    addrlen_ = (socklen_t)sizeof(remote_addr_);
}

std::string UDPSocket::Receive()
{
    int recvlen = recvfrom(fd_of_this_socket_, buf_, UDPSocket::bufsize(), 0, \
        (struct sockaddr*)&remote_addr_, &addrlen_);
        
    return buf_;
}

std::string UDPSocket::GetRemoteAddr()
{
    //return remote_addr_.sin_addr
 return  "";   
    
}

std::string UDPSocket::GetRemotePort()
{
 return  "";   
}

namespace S
{

SockAddr::SockAddr(const std::string &host, const std::string& service)
{
    
}



}


