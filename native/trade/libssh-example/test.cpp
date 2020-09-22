#include "sftp-client.h"

int main()
{
    std::string host = "localhost";
    std::string user = "root";
    std::string passwd = "root";
    SFTPClient sftp(host, 22, user, passwd);
    sftp.ReadSync("/tmp/build/5MS", "/tmp/build/5MD");
    sftp.WriteSync("/tmp/build/10MS", "/tmp/build/10MD");
}
