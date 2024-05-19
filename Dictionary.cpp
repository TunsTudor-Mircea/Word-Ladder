
#include "Dictionary.h"

#include <fstream>
#include <utility>

using std::ifstream;


Dictionary::Dictionary(map<std::string, vector<std::string>> dictionary) : dict{std::move(dictionary)}
{}

Dictionary::Dictionary(const string& filePath) {
    ifstream file(filePath);

    string word;
    while (getline(file, word))
        for (int index = 0; index < word.size(); ++index) {
            string temp = word;
            temp[index] = '*';

            dict[temp].push_back(word);
        }
}
