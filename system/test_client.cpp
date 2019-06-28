#include "libcxx.h"

using namespace std;

int main()
{
    TCPClient client("127.0.0.1", "1083");
    client.Write("Hello");
    cout << "hello has been written" << endl;
    string response = client.Read();
    cout << "server responses: " << response << endl;
    _exit(0);
}