#include "libcxx.h"

using namespace std;

int main()
{
    TCPServer server("1083");
    S::Socket conn = server.Accept();
    cout << "server has accepted" << endl;    
    conn.Read();
    string from_client = conn.str();
    cout << "client says: " << from_client << endl;
    conn.Write("Fuck off\n");
    exit(0);
}