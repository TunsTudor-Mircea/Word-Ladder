
#include "Gamemodes.h"

#include <iostream>
#include <exception>
#include <chrono>
#include <fstream>
#include <set>
#include <string.h>


using std::cout;
using std::cin;
using std::exception;
using std::chrono::system_clock;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::set;


void createUserFile(vector<string>& attempts, vector<string>& validAttempts, const time_t& gameTime,
                    const string& username, int hintCounter, int solutionNrSteps) {
    ofstream file(username + ".csv", std::ios::app);

    file << "Completed at," << ctime(&gameTime) << "\n";

    file << username << "'s attempts,";
    for (auto& attempt : attempts)
        file << attempt << ',';
    file << "\n";

    file << "Valid attempts,";
    for (auto& attempt : validAttempts)
        file << attempt << ',';

    file << "\n";
    file << "Number of attempts," << attempts.size() - 1 << "\n";
    file << "Best possible score was," << solutionNrSteps << "\n";
    file << "Number of hints used," << hintCounter << "\n";
    file << endl;

    file.close();
}


void automaticMode() {
    string startingWord, targetWord;

    cout << "Input starting word: \n";
    cin >> startingWord;

    cout << "Input target word: \n";
    cin >> targetWord;

    if (startingWord.length() != targetWord.length())
        throw std::length_error("The words must have the same number of letters.\n");

    Graph<string> graph;
    Dictionary dictionary("EnglishDictionaries/" + std::to_string(startingWord.size()) + ".txt");
    dictionary.generateDictionaryGraph(graph);

    vector<string> path;
    graph.getBFSPath(startingWord, targetWord, path);

    if (!graph.isNode(startingWord)) {
        cout << "Invalid starting word.\n";
        return;
    }

    if (!graph.isNode(targetWord)) {
        cout << "Invalid target word.\n";
        return;
    }

    if (path.empty())
        throw exception();

    for (string& word : path)
        cout << word << " ";

    cout << std::endl;
}


void playingMode() {
    string username;
    cout << "Input name: ";
    cin >> username;

    int wordLength;
    cout << "Input word length: ";
    cin >> wordLength;

    Graph<string> graph;
    Dictionary dictionary("EnglishDictionaries/" + std::to_string(wordLength) + ".txt");
    dictionary.generateDictionaryGraph(graph);

    string startingWord = graph.getRandomNode(), targetWord = graph.getRandomNode();
    while (startingWord == targetWord)
        targetWord = graph.getRandomNode();

    vector<string> attempts;
    vector<string> validAttempts;

    attempts.push_back(startingWord);
    validAttempts.push_back(startingWord);

    int hintCounter = 0, attemptCounter = 0;

    string currentAttempt = startingWord;

    while (currentAttempt != targetWord) {
        cout << "current word: " << validAttempts.back() << " >>> " << targetWord << " (type 'hint' for help)\n";
        cout << "next word: ";
        cin >> currentAttempt;

        if (currentAttempt == "exit") {
            return;
        }

        else if (currentAttempt == "hint") {
            vector<string> hintPath;
            string lastValidAttempt = validAttempts.back();

            graph.getBFSPath(lastValidAttempt, targetWord, hintPath);

            string hintWord = hintPath.at(1);

            for (int index = 0; index < hintWord.size(); ++index) {
                if (lastValidAttempt[index] != hintWord[index])
                    cout << "<" << lastValidAttempt[index] << ">";

                else
                    cout << lastValidAttempt[index];
            }

            cout << "\n";

            hintCounter++;
        }

        else if (graph.isNode(currentAttempt)) {
            if (currentAttempt.size() != wordLength)
                cout << "Invalid number of letters.\n";

            else {
                int numberOfDifferentLetters = 0;

                for (int index = 0; index < wordLength; ++index)
                    if (currentAttempt[index] != validAttempts.back()[index])
                        numberOfDifferentLetters++;

                if (numberOfDifferentLetters > 1)
                    cout << "The next word should be obtained by replacing only one letter from the previous word.\n";

                else
                    validAttempts.push_back(currentAttempt);
            }

            attempts.push_back(currentAttempt);
        }

        else {
            attempts.push_back(currentAttempt);

            cout << currentAttempt << " is not a valid word.\n";
        }

        attemptCounter++;
    }

    cout << "\nGAME OVER\n";

    const time_t gameTime = system_clock::to_time_t(system_clock::now());
    cout << "Completed at: " << ctime(&gameTime) << "\n";

    cout << username << "'s attempts:\n";

    for (auto& attempt : attempts)
        cout << attempt << "\n";


    vector<string> solution;
    graph.getBFSPath(startingWord, targetWord, solution);

    cout << "\nNumber of attempts: " << attemptCounter << "(best possible score was " << solution.size() - 1 << ")\n";
    cout << "Number of hints used: " << hintCounter << "\n\n";

    createUserFile(attempts, validAttempts, gameTime, username, hintCounter, solution.size() - 1);
}

void analyticsModule(const string& username) {
    ifstream file(username + ".csv");

    if(!file.is_open())
        throw exception();

    string line;
    set<string> uniqueWords;

    while (getline(file, line)) {
        if (line.empty())
            continue;

        std::istringstream iss(line);
        string word;
        iss >> word;

        if (word == "Valid") {
            string current;

            while (getline(iss, current, ','))
                if (!current.empty() && current != " attempts")
                    uniqueWords.insert(current);
        }
    }

    cout << "Unique words: \n";

    for (const auto& word : uniqueWords)
        cout << word << "\n";

    file.close();
}
