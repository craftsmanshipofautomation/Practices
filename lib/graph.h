#ifndef LIB_GRAPH_H
#define LIB_GRAPH_H
#include <list>
#include <map>

// supported by https://algs4.cs.princeton.edu/44sp/

class GraphMachine
{
  public:
    GraphMachine(const std::string&);
    void PrintDigraph();

  private:
    struct GraphEdge
    {
        int start;
        int end;
        double weight;
    };
    typedef std::map<int, std::list<GraphEdge>> Digraph;
    struct EWDReader
    {
       EWDReader(const std::string&, Digraph&);
    };
    Digraph digraph_;
};

#endif