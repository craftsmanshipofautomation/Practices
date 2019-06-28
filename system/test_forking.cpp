#include "libcxx.h"

TEST_BEGIN

using namespace std;

TEST(FORK, WAIT)
{
    pid_t pid = Fork();
    switch (pid)
    {
        case 0:
            cout << "child" << endl;
            exit(42);
        case -1:
            terminate();
        default:
            cout << "parent" << endl;
            int status;
            while ((pid = waitpid(-1, &status, 0)) > 0)
            {
                if (WIFEXITED(status))
                    cout << "child exited with " << WEXITSTATUS(status) << endl; 
                else
                    cout << "child exited abnornally" << endl;                                
            }
    }
}

TEST_END