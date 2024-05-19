#include "Graph.h"

#include <algorithm>
#include <exception>
#include <queue>
#include <string>
#include <random>

using std::find;
using std::exception;
using std::queue;
using std::string;

template <class T>
Graph<T>::Graph(const vector<T>& nodes, const map<T, vector<T>>& neighborList) :
    nodes{nodes},
    neighborList{neighborList}
{}

template <class T>
void Graph<T>::addNode(const T &node) {
    if (isNode(node))
        throw exception();

    nodes.push_back(node);
}

template <class T>
void Graph<T>::addEdge(const T &origin, const T &destination) {
    if (!isNode(origin))
        throw exception();

    if (!isNode(destination))
        throw exception();

    neighborList[origin].push_back(destination);
    neighborList[destination].push_back(origin);
}

template <class T>
bool Graph<T>::isNode(const T &node) {
    if (find(nodes.begin(), nodes.end(), node) != nodes.end())
        return true;

    return false;
}

template <class T>
vector<T> Graph<T>::getNeighbors(const T &node) {
    if (!isNode(node))
        throw exception();

    return neighborList[node];
}

template <class T>
T Graph<T>::getRandomNode() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, nodes.size() - 1);

    return nodes[dis(gen)];
}

template <class T>
int Graph<T>::findIndexByNode(const T & node) {
    int index = 0;

    for (auto& currentNode : nodes) {
        if (currentNode == node)
            return index;

        index++;
    }

    throw exception();
}

template <class T>
void Graph<T>::getBFSPath(const T &origin, const T &destination, vector<T>& path) {
    if (!isNode(origin))
        throw exception();

    if (!isNode(destination))
        throw exception();

    vector<bool> visited(nodes.size(), false);
    vector<int> parent(nodes.size());
    queue<T> queue;

    int originIndex = findIndexByNode(origin);

    visited[originIndex] = true;
    parent[originIndex] = -1;
    queue.push(origin);

    while(!queue.empty()) {
        T& current = queue.front();
        queue.pop();

        for (auto& neighbor: getNeighbors(current)) {
            int neighborIndex = findIndexByNode(neighbor);
            if (!visited[neighborIndex]) {
                visited[neighborIndex] = true;
                parent[neighborIndex] = findIndexByNode(current);

                queue.push(neighbor);
            }
        }
    }

    for (int index = findIndexByNode(destination); index != -1; index = parent[index])
            path.push_back(nodes.at(index));

    std::reverse(path.begin(), path.end());
}

template class Graph<string>;
