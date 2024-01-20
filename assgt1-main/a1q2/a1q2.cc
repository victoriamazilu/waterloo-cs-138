/*
* CS138, W23, Assignment 1, Problem 2
* Main Function

* Try to keep it as simple as possible
* and implement the logic of your program
* in a1q2.cpp, so that you can write unit tests
* for them and make sure of their expected behavior.
*/

#include <iostream>
#include <string>
using namespace std;

// no argc+argv because we aren't using them in A1
int main() {
    int N;
    char command;
    cin >> N >> command;

    if (N <= 0) {
        cerr << "Error, line length must be positive." << endl;
        return 1;
    }
    if (command != 'f' || command != 'r') {
        cerr << "Error, command is illegal." << endl;
        return 1;
    }
    cin.ignore();

    vector<string> lines;
    string line;

    while (getline(cin, line)) {
        lines.push_back(line);
    } 
    
    if (command == 'f') {
        for (const auto& l : lines) {
            cout << l.substr(0, N) << endl;
        }
    } else if (command == 'r') {
        for (auto it = lines.rbegin(); it != lines.rend(); ++it) {
            cout << it->substr(0, N) << endl;
        }
    } else if (command == 'g') {
        for (const auto& l : lines) {
            if (l.find("fnord") != string::npos) {
                cout << l.substr(0, N) << endl;
            }
        }
    }

    return 0;

    return 0;
}
