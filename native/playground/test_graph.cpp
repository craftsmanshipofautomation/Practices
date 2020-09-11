#include "libcxx.h"

using namespace std;
TEST_BEGIN
#include <exception>
#include <unistd.h>

TEST(GRAPH, CONSTRUCT)
{
    Digraph d = EWDRead("tinyEWD.txt");
    Print(d);
}

TEST(GRAPH, BFS)
{
    try
    {
        Digraph d = EWDRead("simple_graph_1.txt");
        Print(d);
        GRAPH_BFS(&d, 0);
        PrintPath(&d, 0, 3);
    }
    catch (Error &e)
    {
        cout << e.what() << endl;
    }
}

TEST(GRAPH, DFS)
{

    Digraph d = EWDRead("tinyEWD.txt");
    Print(d);
    GRAPH_DFS(&d, 0);
    PrintPath2(&d, 0, 3);
}

TEST(GRAPH, DFS2)
{

    Digraph d = EWDRead("tinyEWD.txt");
    Print(d);
    GRAPH_DFS_2(&d, 0);
    PrintPath2(&d, 0, 3);
}

TEST(GRAPH, Dijkstra)
{
    Digraph d = EWDRead("tinyEWD.txt");
    Print(d);
    Dijkstra(&d, 0);
    PrintPath(&d, 0, 3);
}

TEST(GRAPH, Dijkstra2)
{
    Digraph d = EWDRead("mediumEWD.txt");
    Print(d);
    Dijkstra(&d, 0);
    PrintPath(&d, 0, 6);
}

TEST_END
