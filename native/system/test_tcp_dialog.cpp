#include "libcxx.h"

using namespace std;

int main()
{
    TCPServer server("1082");    
    pid_t pid = Fork();
    if (pid == 0)
        {
            server.Close();
            TCPClient client("127.0.0.1", "1082");
            // it's user's responsibility to provide a newline
            client.Write("Hello, Server\n");
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
            S::Socket conn = server.Accept();
            conn.Read();
            string from_client = conn.str();
            cout << "client says: " << from_client << endl;
            conn.Write("Fuck off\n");
            while ((pid = waitpid(-1, NULL, 0)) > 0)
            {
                
            }
        }
}