// /*
// * CS138, W23, Assignment 1, Problem 4
// * Main Function
// *
// * main function is a special function,
// * which serves as the entry point for the program.
// * 
// * Try to keep it as simple as possible
// * and implement the logic of your program
// * in a1q4.cpp, so that you can write unit tests
// * for them and make sure of their expected behavior.
// */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    int N;
    cin >> N;

    if (N <= 0) {
        cerr << "Error, line length must be positive." << endl;
        return 1;
    }

    cin.ignore();

    vector<string> list;
    string token;

    while (cin >> token) {
        if(token.length() > N){
            list.push_back(token.substr(0, N));
        } else {
            list.push_back(token);
        }
    }

    if (list.size() == 1) {
        cout << list[0] << endl;
        return 0;
    }

    // To calculate the number of lines
    int charCount = list[0].length();
    int lineCount = 1;
    for (int i = 1; i < list.size(); i++) {  // Start from 1 as we already counted list[0]
        if(charCount + 1 + list[i].length() <= N) {
            charCount += 1 + list[i].length();
        } else {
            charCount = list[i].length();
            lineCount++;
        }
    }

    vector<vector<string>> lines(lineCount);
    int lineNumber = 0;
    charCount = list[0].length(); // Reinitialize charCount for the first line
    lines[0].push_back(list[0]);
    for (int i = 1; i < list.size(); i++) {
        if (charCount + 1 + list[i].length() <= N) {
            lines[lineNumber].push_back(list[i]);
            charCount += 1 + list[i].length();
        } else {
            lineNumber++;
            lines[lineNumber].push_back(list[i]);
            charCount = list[i].length();
        }
    }

    // Distribute spaces and justify text
    vector<string> result;
    for (int i = 0; i < lines.size(); i++) {
        int totalLength = 0;
        for (int j = 0; j < lines[i].size(); j++) {
            const string& token = lines[i][j];
            totalLength += token.length();
        }

        
        int spacesNeeded = N - totalLength;
        int gaps = lines[i].size() - 1;
        int spaceBetweenWords;
        int extraSpace;
        
        if (gaps > 0) { //If gaps are needed, calculate the amount of spaces to distribute per word
            spaceBetweenWords = spacesNeeded / gaps;
            extraSpace = spacesNeeded % gaps;
        } else {
            spaceBetweenWords = 0;
            extraSpace = 0;
        }

        string justifiedLine;
        for (int j = 0; j < lines[i].size(); j++) {
        justifiedLine += lines[i][j];  // add the word
        if (j < lines[i].size() - 1) {  // check if it's not the last word
            justifiedLine += string(spaceBetweenWords, ' ');  // Add the regular spaces between the words
            if (extraSpace > 0) {
                justifiedLine += " ";  // add one extra space if needed and not distributes yet
                extraSpace--;  // Decrement the extra spaces
            }
        }
    }
        
        // If there's only one token or the last token in the line, pad the end with spaces
        if (justifiedLine.length() < N) {
            justifiedLine += string(N - justifiedLine.length(), ' ');
        }
        
        result.push_back(justifiedLine);
    }



    // Printing
    for (int i = 0; i < lineCount; i++) {
        cout << result[i] << endl;
    }

    return 0;
}
