#include <libssh/sftp.h>
#include <cstdio>
#include <string>
#include <cstring>
#include <exception>
#include <sys/stat.h>
#include <fcntl.h>

// Good chunk size
#define MAX_XFER_BUF_SIZE 16384

class SFTPException : public std::exception
{
public:
    SFTPException(const char *msg) : msg_(msg) {}
    ~SFTPException() {}
    const char *what() const throw() { return msg_.c_str(); }

private:
    std::string msg_;
};

/// 封装 SSH 资源
class SSHRC
{
public:
    SSHRC()
    {
        s_ = ssh_new();
        if (s_ == NULL)
            throw SFTPException("Failed to create SSH session");
    }
    ssh_session session() { return s_; }
    ~SSHRC() { ssh_free(s_); }

private:
    ssh_session s_;
};

class SSHSession
{
public:
    SSHSession(std::string &host, int port, std::string &username, std::string &password);
    ~SSHSession();
    ssh_session get() { return sshrc_.session(); }
    int VerifyKnownServer();
    void AuthenticateWithPassword();

private:
    SSHRC sshrc_;
    std::string username_;
    std::string password_;
};

class SFTPRC
{
public:
    SFTPRC(SSHSession &s)
    {
        s_ = sftp_new(s.get());
        if (s_ == NULL)
            throw SFTPException("Failed to create new SFTPSession");
    }
    ~SFTPRC() { sftp_free(s_); }
    inline sftp_session session() { return s_; }

private:
    SFTPRC() {}
    sftp_session s_;
};

class SFTPSession
{
public:
    SFTPSession(SSHSession &);
    ~SFTPSession();
    inline sftp_session get() { return sftprc_.session(); }

private:
    SFTPRC sftprc_;
};

class STFPFile
{
public:
    STFPFile(SFTPSession &sftp, std::string remote, int remote_access_type, std::string local, int local_access_type)
    {
        /// 需要指定 permission
        file_ = sftp_open(sftp.get(), remote.c_str(),
                          remote_access_type, S_IREAD | S_IWRITE | S_IRGRP | S_IROTH);
        if (file_ == NULL)
            throw SFTPException("Can't open sftp file");
        fd_ = open(local.c_str(), local_access_type);
        if (fd_ < 0)
            throw SFTPException("Can't open local file");
    }
    ~STFPFile() { sftp_close(file_); }
    sftp_file remote() { return file_; }
    int local() { return fd_; }

private:
    sftp_file file_;
    int fd_;
};

class SFTPClient
{
public:
    SFTPClient(std::string &host, int port, std::string &username, std::string &password);
    ~SFTPClient();

    /// 内部实现
public:
    void ReadSync(std::string src, std::string dest);
    void WriteSync(std::string src, std::string dest);

private:
    SSHSession ssh_ss_;
    SFTPSession sftp_ss_;
};
