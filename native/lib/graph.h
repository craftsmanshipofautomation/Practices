#ifndef LIB_GRAPH_H
#define LIB_GRAPH_H
#include <list>
#include <map>

// must read introduction to algorithms in a systematic way
// , else many efforts are spent in vain
#define GRAPH_INF std::numeric_limits<double>::infinity()

enum GraphColor
{
    white,
    black,
    gray
};

struct Vertex
{
    Vertex(int n, double d = GRAPH_INF, Vertex *p = nullptr,
           GraphColor c = GraphColor::white)
        : number(n), distance(d), predecessor(p), color(c), discover_time(0),
          finishing_time(0), callback(nullptr)
    {
    }
    int number;
    double distance;
    Vertex *predecessor;
    GraphColor color;
    int discover_time;
    int finishing_time;
    Vertex *callback;
    bool visited;

  private:
    Vertex() {}
};

struct Edge
{
    Vertex *to;
    double weight;
};

// vertices start from 0 to N, must be continuous,
// not gap is allowed, for those vertice whose label is not number
// , write an adapter for them
struct Digraph
{
    Digraph(int vn, int en);
    Digraph(Digraph &&d);
    Digraph(Digraph &d);
    void Push(int from, int to, double weight);
    void SetColor(int v, GraphColor);
    void SetDistance(int v, double);
    double Distance(int v);
    void SetPredecessor(int s, int v);
    void SetPredecessor(int s, Vertex *);
    Vertex *Predecessor(int v);
    void Check(int);
    Vertex* V(int s);
    std::vector<Edge> Adjacent(int v);
    std::vector<Edge> Adjacent(Vertex*);    
    std::map<int, std::vector<Edge>> adjacency_list;
    std::vector<Vertex> vertices;
    int vertex_number;
    int edge_number;

    // inlines
    inline void Check(Vertex *v)
    {
        for (auto &i : vertices)
        {
            if (&i == v)
                return;
        }
        throw Error("No Such Vertex");
    }
    inline double Distance(Vertex *v)
    {
        Check(v);
        return v->distance;
    }
    inline void SetDistance(Vertex *v, double d)
    {
        Check(v);
        v->distance = d;
    }
    inline GraphColor Color(Vertex* v)
    {
        Check(v);
        return v->color;
    }
    inline void SetPredecessor(Vertex *s, Vertex *v)
    {
        Check(v);
        s->predecessor = v;
    }    
};

void Print(const Digraph &);
Digraph EWDRead(const std::string &);

// bfs to search for vertices that are reachable from s
// but not necessary to enumerate traversal paths
void GRAPH_BFS(Digraph *, int);
// so far, I see this function print only one path.
// the last modification of predecessor detemined which path to be printed
void PrintPath(Digraph *, int, int);
void PrintPath2(Digraph *, int, int);

void GRAPH_DFS(Digraph *, int);
// the non-recursion version can't record time,
// or too complecated
// for example
//   0
//
// 2   4
// first of all, 0 in the stack
// then is pop out; 2 4 in, 4 will be handled first, vertex 2 must have a
// reference to 4, so when 2 is dealt with, it will modify 4's finishing time
//, and so forth, after 2 's done, 0's time will be updated;
// it's error-prone, I will not waste my time here.
void GRAPH_DFS_2(Digraph *, int);

void Dijkstra(Digraph *, int s);

#endif