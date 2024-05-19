
#ifndef EXTRACREDIT3_DICTIONARY_H
#define EXTRACREDIT3_DICTIONARY_H

#include "Graph.h"

#include <string>

using std::string;

class Dictionary {
private:
    map<string, vector<string>> dict;

public:
    Dictionary() = default;
    explicit Dictionary(map<string, vector<string>>);
    explicit Dictionary(const string&);

    template <typename T>
    void generateDictionaryGraph(Graph<T>& graph) {
        for (auto& pair : dict) {
            vector<string> words = pair.second;

            if (words.size() > 1)
                for (int index1 = 0; index1 < words.size() - 1; ++index1) {
                    if (!graph.isNode(words[index1]))
                        graph.addNode(words[index1]);

                    for (int index2 = index1 + 1; index2 < words.size(); ++index2) {
                        if (!graph.isNode(words[index2]))
                            graph.addNode(words[index2]);

                        graph.addEdge(words[index1], words[index2]);
                    }
                }
        }
    }

    ~Dictionary() = default;

};


#endif //EXTRACREDIT3_DICTIONARY_H
