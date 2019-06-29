#include "libcxx.h"
#include <map>
#include <unistd.h>
using namespace std;

int main()
{
    fd_set master;
    fd_set read_fds;
    int fdmax;

    FD_ZERO(&master);
    FD_ZERO(&read_fds);

    TCPServer server("1083");
    int listener = server.fd();

    FD_SET(listener, &master);
    fdmax = listener;
    map<int, S::Socket> sockets;
    for (;;)
    {
        read_fds = master;
        if (Select(fdmax + 1, &read_fds, NULL, NULL, NULL) == -1)
        {
            exit(-1);
        }
        for (int i = 0; i <= fdmax; ++i)
        {
            // sth stirs in the east
            if (FD_ISSET(i, &read_fds))
            {
                if (i == listener)
                {
                    cout << "accept" << endl;
                    S::Socket conn = server.Accept();
                    int fd = conn.fd();
                    FD_SET(fd, &master); // add to master set
                    if (fd > fdmax)
                    {
                        fdmax = fd;
                    }
                    sockets[fd] = std::move(conn);
                }
                else
                {
                    auto s = sockets.find(i);
                    if (s != sockets.end())
                    {
                        int nbytes;
                        // changes happen to fd, may be shutting down,
                        // may be message comming
                        if ((nbytes = s->second.Read()) <= 0)
                        {
                            if (nbytes == 0)
                            {
                                cout << "client " << i << " hung up" << endl;
                            }
                            sockets.erase(s);
                            FD_CLR(i, &master);
                        }
                        else
                        {
                            cout << "client " << i
                                 << " says: " << s->second.str() << endl;
                            s->second.Write("Greeting\n");
                        }
                    }
                }
            }
        }
    }
}