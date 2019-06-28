#include "libcxx.h"

using namespace std;

int main()
{
    TCPServer server("1083");
    server.Accept();
    cout << "server has accepted" << endl;    
    string from_client = server.Read();
    cout << "client says: " << from_client << endl;
    server.Write("Fuck off");
    exit(0);
}