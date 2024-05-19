
#ifndef EXTRACREDIT3_GRAPH_H
#define EXTRACREDIT3_GRAPH_H

#include <iomanip>
#include <vector>
#include <map>

using std::vector;
using std::map;

using std::ostream;

template <class T>

class Graph {
private:
    vector<T> nodes;
    map<T, vector<T>> neighborList;

public:
    Graph() = default;
    Graph(const vector<T>&, const map<T, vector<T>>&);

    void addNode(const T&);
    void addEdge(const T&, const T&);

    bool isNode(const T&);
    vector<T> getNeighbors(const T&);
    T getRandomNode();

    int findIndexByNode(const T&);
    void getBFSPath(const T&, const T&, vector<T>&);

    ~Graph() = default;
};

#endif //EXTRACREDIT3_GRAPH_H
