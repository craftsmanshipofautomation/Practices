#include "libcxx.h"
#include <exception>

using namespace std;

Digraph::Digraph(int vn, int en) : vertex_number(vn), edge_number(en)
{
    for (int i = 0; i < vertex_number; ++i)
    {
        vertices.push_back(Vertex(i));
    }
}

Digraph::Digraph(Digraph &&d)
    : adjacency_list(move(d.adjacency_list)), vertices(move(d.vertices)),
      vertex_number(d.vertex_number), edge_number(d.edge_number)
{
}

Digraph::Digraph(Digraph &d) {}

void Digraph::Push(int from, int to, double weight)
{
    adjacency_list[from].push_back({&vertices[to], weight});
}

Digraph EWDRead(const std::string &dpath)
{
    ifstream src(dpath);
    if (!src.good())
    {
        throw Error(dpath + ": No such file\n");
    }
    // protocol: first line contains vertex number
    //           second line : number of edges
    // the following: edges with weight;
    std::string line;
    int vertex_number, edge_number;
    int from, to;
    double weight;
    string temp;
    getline(src, line);
    vertex_number = stoi(line);
    getline(src, line);
    edge_number = stoi(line);
    Digraph digraph(vertex_number, edge_number);

    for (int i = 0; i < edge_number; ++i)
    {
        if (getline(src, line))
        {
            istringstream is(line);
            is >> from;
            is >> to;
            is >> weight;
            digraph.Push(from, to, weight);
        }
    }

    src.close();
    return std::move(digraph);
}

void Print(const Digraph &digraph)
{
    for (auto &m__ : digraph.adjacency_list)
    {
        for (auto &vertex : m__.second)
        {
            cout << m__.first << "->" << vertex.to->number << " ("
                 << vertex.weight << ")" << endl;
        }
    }
}

void Digraph::Check(int v)
{
    if (!(v >= 0 && v < vertex_number))
    {
        string error = string("Error at line ") + to_string(__LINE__) + ": " +
                       "Invalid vertex: " + to_string(v);
        throw Error(error);
    }
}

void Digraph::SetColor(int v, GraphColor c)
{
    Check(v);
    vertices[v].color = c;
}

void Digraph::SetDistance(int v, double d)
{
    Check(v);
    vertices[v].distance = d;
}

void Digraph::SetPredecessor(int s, int v)
{
    Check(v);
    Check(s);
    vertices[s].predecessor = &vertices[v];
}

void Digraph::SetPredecessor(int s, Vertex *vert)
{
    Check(s);
    vertices[s].predecessor = vert;
}

std::vector<Edge> Digraph::Adjacent(int v)
{
    Check(v);
    return adjacency_list[v];
}

std::vector<Edge> Digraph::Adjacent(Vertex* v)
{
    Check(v);
    return adjacency_list[v->number];
}

double Digraph::Distance(int v)
{
    Check(v);
    return vertices[v].distance;
}

Vertex *Digraph::Predecessor(int v)
{
    Check(v);
    return vertices[v].predecessor;
}

Vertex* Digraph::V(int s)
{
    Check(s);
    return &vertices[s];
}

void GRAPH_BFS(Digraph *digraph, int s)
{
    queue<int> Q;
    digraph->SetDistance(s, 0);
    Q.push(s);
    while (!Q.empty())
    {
        int u = Q.front();
        double udist = digraph->Distance(u);
        Q.pop();
        for (auto &v : digraph->Adjacent(u))
        {
            int vv = v.to->number;
            if (v.to->color == GraphColor::white)
            {
                digraph->SetColor(vv, GraphColor::gray);
                digraph->SetDistance(vv, udist + v.weight);
                digraph->SetPredecessor(vv, u);
                Q.push(vv);
            }
        }
        digraph->SetColor(u, GraphColor::black);
    }
}

void PrintPath__(Digraph *digraph, int s, int v)
{
    if (s == v)
        cout << " " << s << "(" << digraph->Distance(s) << ")";
    else if (digraph->Predecessor(v) == nullptr)
        cout << "no path from " << s << " to " << v << endl;
    else
    {
        PrintPath__(digraph, s, digraph->Predecessor(v)->number);
        cout << " " << v << "(" << digraph->Distance(v) << ")";
    }
}
void PrintPath(Digraph *digraph, int s, int v)
{
    PrintPath__(digraph, s, v);
    cout << endl;
}

void PrintPath2__(Digraph *digraph, int s, int v)
{
    if (s == v)
        cout << " " << s << "(" << digraph->vertices[s].discover_time << "/"
             << digraph->vertices[s].finishing_time << ")";
    else if (digraph->Predecessor(v) == nullptr)
        cout << "no path from " << s << " to " << v << endl;
    else
    {
        PrintPath2__(digraph, s, digraph->Predecessor(v)->number);
        cout << " " << v << "(" << digraph->vertices[v].discover_time << "/"
             << digraph->vertices[v].finishing_time << ")";
    }
}
void PrintPath2(Digraph *digraph, int s, int v)
{
    PrintPath2__(digraph, s, v);
    cout << endl;
}

void DFS_VISIT(Digraph *digraph, int s)
{
    static int time = 0;
    ++time;
    auto &vertex_s = digraph->vertices[s];
    vertex_s.discover_time = time;
    digraph->SetColor(s, GraphColor::gray);
    for (auto &edge : digraph->Adjacent(s))
    {
        if (edge.to->color == GraphColor::white)
        {
            digraph->SetPredecessor(edge.to->number, s);
            DFS_VISIT(digraph, edge.to->number);
        }
    }
    digraph->SetColor(s, GraphColor::black);
    ++time;
    vertex_s.finishing_time = time;
}

void GRAPH_DFS(Digraph *digraph, int s)
{
    static int time = 0;
    for (auto &vertex : digraph->vertices)
    {
        if (vertex.color == GraphColor::white)
            DFS_VISIT(digraph, vertex.number);
    }
}

void GRAPH_DFS_2(Digraph *digraph, int s)
{
    static int time2 = 0;
    std::stack<int> stack;
    Vertex *last;
    stack.push(s);
    auto &vertex_s = digraph->vertices[s];
    vertex_s.discover_time = time2;
    while (!stack.empty())
    {
        int u = stack.top();
        stack.pop();
        digraph->vertices[u].discover_time = time2;
        time2++;
        digraph->SetColor(u, GraphColor::gray);
        if (digraph->vertices[u].callback)
        {
            digraph->vertices[u].callback->finishing_time = time2;
            digraph->vertices[u].callback->color = GraphColor::black;
        }
        if (digraph->Adjacent(u).size() > 0)
        {
            digraph->Adjacent(u)[0].to->callback = &digraph->vertices[u];
        }
        else
        {
            digraph->vertices[u].finishing_time = time2;
            time2++;
        }
        for (auto &edge : digraph->Adjacent(u))
        {
            if (edge.to->color == GraphColor::white)
            {
                digraph->SetPredecessor(edge.to->number, u);
                stack.push(edge.to->number);
            }
        }
    }
}

void Dijkstra(Digraph *G, int s)
{
    auto cmp = [](Vertex* lhs, Vertex* rhs)
    {
        cout << lhs->distance << " " <<  rhs->distance << endl;                
        return lhs->distance < rhs->distance;
    };
    std::priority_queue<Vertex*, std::vector<Vertex*>, decltype(cmp)> Q(cmp);
    Q.push(G->V(s));
    G->SetColor(s, GraphColor::white);
    G->SetDistance(s, 0);
    while (!Q.empty())
    {
        auto u = Q.top();
        Q.pop();
        u->color = GraphColor::gray;
        auto edges = G->Adjacent(u);
        for (auto &edge : edges)
        {
            if (G->Color(edge.to) == GraphColor::white)
            {
                if (G->Distance(edge.to) > G->Distance(u) + edge.weight)
                {
                    G->SetDistance(edge.to, G->Distance(u) + edge.weight);
                    G->SetPredecessor(edge.to, u);                    
                    Q.push(edge.to);                    
                }
            }
        }
        u->color = GraphColor::black;
    }
}

