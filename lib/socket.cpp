#include "socket.h"
#include <iostream>

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
        Close(fd_);
    if (buf_)
        delete[] buf_;
    if (rio_)
        delete rio_;
}

size_t Socket::Write(const char* str)
{
    int len = strlen(str);
    if (len > MAXLINE-1)
        len = MAXLINE-1;
    strncpy(buf_, str, len);
    buf_[len] = '\n'; // this is fatal
    Rio_writen(fd_, buf_, len+1);
    return len;
}

size_t Socket::Read()
{
    Rio_readinitb(rio_, fd_);    
    bufsize_ = Rio_readlineb(rio_, buf_, MAXLINE); // including '\n'
    return bufsize_;
}

const char* Socket::str()
{
    if (bufsize_ > 0)
        buf_[bufsize_-1] = '\0';
    return buf_;
}

} // namespace S

LSocket::LSocket(int fd) : lfd_(fd), clientlen_(sizeof(struct sockaddr_storage))
{
}

LSocket::~LSocket()
{
    Close(lfd_);
}

S::Socket LSocket::Accept()
{
    int connfd = ::Accept(lfd_, (SA *)&clientaddr_, &clientlen_);
    S::Socket ret(connfd);
    Getnameinfo((SA *)&clientaddr_, clientlen_, client_hostname_, MAXLINE,
                client_port_, MAXLINE, 0);
    return std::move(ret);
}

