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
#include <vector>
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
    if (command != 'f' && command != 'r' && command != 'g') {
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
        for (int i = 0; i < lines.size(); ++i) {
            if (lines[i].length() > N) {
                cout << lines[i].substr(0, N) << endl;
            } else {
                cout << lines[i] << endl;
            }
        }
    } else if (command == 'r') {
        //print the array in reverse
        for (int i = lines.size() - 1; i >= 0; i--) {   
            if (lines[i].length() > N) {
                cout << lines[i].substr(0, N) << endl;
            } else {
                cout << lines[i] << endl;
            }
        }
    } else { //command == 'g'
        for (int i = 0; i < lines.size(); i++) {
            int index = lines[i].find("fnord", 0);
            // Check if "fnord" was found
            if (index < lines[i].length()) {
                // Found "fnord", print up to N characters of this line
                if (lines[i].length() > N) {
                    cout << lines[i].substr(0, N) << endl;
                } else {
                    cout << lines[i] << endl;
                }
            }
        }
    }
    
    return 0;
}
