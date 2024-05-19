#include "Gamemodes.h"
#include <iostream>

using std::cout;
using std::cin;

void showUI() {
    cout << "Select an option: \n";
    cout << "[1] Automatic Mode\n";
    cout << "[2] Playing Mode\n";
    cout << "[3] Analytics\n";
    cout << "[4] Help\n";
    cout << "[0] Exit\n";
    cout << "Enter option: ";
}

void helpUI() {
    cout << "You will be assigned a starting word and a target word.\n";
    cout << "At each step of the game, you must change a single letter of the word into another word.\n";
    cout << "(it is forbidden to transform a word into a non-word)\n";
    cout << "The goal is to reach the target word by using such transformations of words.\n";
    cout << "Good luck!" << std::endl;
}

int main() {
    while (true) {
        showUI();
        string userInput;
        cin >> userInput;
        cout << std::endl;

        if (userInput == "1") {
            try {
                automaticMode();
            }

            catch (std::exception& e) {
                cout << "Cannot find solution.\n";
            }
        }

        else if (userInput == "2") {
            try {
                playingMode();
            }

            catch (std::exception& e) {
                cout << e.what();
            }
        }

        else if (userInput == "3") {
            try {
                string username;
                cout << "Enter user name: ";
                cin >> username;

                analyticsModule(username);
            }
            catch (std::exception&) {
                cout << "The user doesn't have any record.\n";
            }
        }

        else if (userInput == "4") {
            helpUI();
        }

        else if (userInput == "0") {
            cout << "Closing program...";
            break;
        }

        else {
            cout << "Invalid input.\n";
        }
    }

    return 0;
}
