#include "libcxx.h"

using namespace std;

GraphMachine::EWDReader::EWDReader(const std::string &ewd_path,
                                   Digraph &digraph)
{
    ifstream src(ewd_path);
    if (!src.good())
    {
        throw ewd_path + ": No such file\n";
    }

    // protocol: first line contains vertex number
    //           second line : number of edges
    // the following: edges with weight;
    std::string line;
    int vertex_number, edge_number;
    int start, end;
    double weight;
    string temp;
    getline(src, line);
    vertex_number = stoi(line);
    getline(src, line);
    edge_number = stoi(line);

    for (int i = 0; i < edge_number; ++i)
    {
        getline(src, line);
        istringstream is(line);
        is >> start;
        is >> end;
        is >> weight;
        
        digraph[start].push_back({start, end, weight});
    }
    if (digraph.size() != (size_t)vertex_number)
        throw "wrong EWD file format!";
}

GraphMachine::GraphMachine(const std::string &ewd_path)
{
    EWDReader(ewd_path, digraph_);
}


void GraphMachine::PrintDigraph()
{
    for(auto& iter : digraph_)
    {
        auto& l__ = iter.second;
        for (auto& node : l__)
        {
            cout << node.start << "->" << node.end << " (" << node.weight << ")" << endl;
        }
    }
}
