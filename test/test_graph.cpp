#include "libcxx.h"

using namespace std;
TEST_BEGIN

TEST(GRAPH, CONSTRUCT)
{
    GraphMachine GM(string("tinyEWD.txt"));
    GM.PrintDigraph();
    
}

TEST_END