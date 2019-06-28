#include "libcxx.h"

using namespace std;

int main()
{
    TCPServer server("1082");    
    pid_t pid = Fork();
    if (pid == 0)
        {
            TCPClient client("127.0.0.1", "1082");
            client.Write("Hello, Server");
            string response = client.Read();
            cout << "server responses: " << response << endl;
            _exit(0);
        }
    else if (pid == -1)
        {
            terminate();
        }
    else
        {
            server.Accept();
            string from_client = server.Read();
            cout << "client says: " << from_client << endl;
            server.Write("Fuck off\n");
            while ((pid = waitpid(-1, NULL, 0)) > 0)
            {
                
            }
        }
}