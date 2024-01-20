/*
* CS138, W23, Assignment 1, Problem 5
* Main Function
*
* main function is a special function,
* which serves as the entry point for the program.
* 
* Try to keep it as simple as possible
* and implement the logic of your program
* in a1q5.cpp, so that you can write unit tests
* for them and make sure of their expected behavior.
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// c1 functions
vector<string> raggedRight(vector<string> list, int N) {
    string currentLine = "";
    vector<string> result;

    for (int i = 0; i < list.size(); i++) { // iterating through each word in list vector
        if (currentLine.size() + list[i].size() + (currentLine.size() > 0) <= N) { // if theres space, execute
            if(currentLine.size() > 0){ // if not empty, add space and word
                currentLine += " ";
            }
            currentLine += list[i];
        } else{ // if theres no space left, execute
            result.push_back(currentLine); // push it to output 
            currentLine = list[i]; //reset 
        }
    }
    if (!currentLine.empty()) { // this adds the remaining list to output even though they havent reached max`
        result.push_back(currentLine);
    }

    for (int i = 0; i < result.size(); i++) {
        int spacesNeeded = N - result[i].length();
        if (result[i].length() < N) {
            result[i] = result[i] + string(spacesNeeded, ' ');
        }
    }

    return result;
}
vector<string> justify(vector<string>list,int N){
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

    // Store all of the sentences in a 2D array for easy manipulation
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

    // Distribute spaces and justify text for each line
    vector<string> result;
    for (int i = 0; i < lines.size(); i++) { // total length needed so calculate by adding each token length
        int totalLength = 0;
        for (int j = 0; j < lines[i].size(); j++) {
            const string& token = lines[i][j];
            totalLength += token.length();
        }

        // Important info needed to solve 
        int spacesNeeded = N - totalLength; //--spaces needed: total amount of spaces to distribute
        int gaps = lines[i].size() - 1;     //--amount of gaps between the words
        int spaceBetweenWords;              //--will change depending on if theres more than one word
        int extraSpace;                     //--if uneven amount
        
        if (gaps > 0) { // if gaps are needed then distribute the split spaces needed and add any extra spaces
            spaceBetweenWords = spacesNeeded / gaps;
            extraSpace = spacesNeeded % gaps;
        } else { //else theyre are no extra space between words
            spaceBetweenWords = 0;
            extraSpace = 0;
        }

        string justifiedLine;
        for (int j = 0; j < lines[i].size(); j++) {
            justifiedLine += lines[i][j];
            if (gaps > 0 && j < gaps) { //if gaps are needed and
                if (j < extraSpace) {
                    justifiedLine += string(spaceBetweenWords + 1, ' ');
                } else {
                    justifiedLine += string(spaceBetweenWords, ' ');
                }
            }
        }
        
        // If there's only one token or the last token in the line, pad the end with spaces
        if (justifiedLine.length() < N) {
            justifiedLine += string(N - justifiedLine.length(), ' ');
        }
        
        result.push_back(justifiedLine);
        
    }
    return result;
}
vector<string> raggedLeft(vector<string>list,int N){
    string currentLine = "";
    vector<string> result;

    for (int i = 0; i < list.size(); i++) { // iterating through each word in list vector
        if (currentLine.size() + list[i].size() + (currentLine.size() > 0) <= N) { // if theres space, execute
            if(currentLine.size() > 0){ // if not empty, add space and word
                currentLine += " ";
            }
            currentLine += list[i];
        } else{ // if theres no space left, execute
            result.push_back(currentLine); // push it to output 
            currentLine = list[i]; //reset 
        }
    }
    if (!currentLine.empty()) { // this adds the remaining list to output even though they havent reached max`
        result.push_back(currentLine);
    }

    for (int i = 0; i < result.size(); i++) {
        int spacesNeeded = N - result[i].length();
        if (result[i].length() < N) {
            result[i] = string(spacesNeeded, ' ') + result[i];
        }
    }

    return result;
}
vector<string> centre(vector<string>list,int N){
    //To calculate the amount of lines needed
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

    // Store all of the sentences in a 2D array for easy manipulation
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
        vector<string> line = lines[i];
        int totalLength = 0;
        for (int j = 0; j < line.size(); j++) {
            totalLength += line[j].length();
        }
        totalLength += line.size() - 1; // Add spaces between words
        
        int spacesNeeded = N - totalLength;
        int spaceBetweenWords = line.size() - 1;
        int padding = spacesNeeded / 2;
        int extraSpace = spacesNeeded % 2; // In case of an odd number of spaces

        string newLine = string(padding + extraSpace, ' '); // Left padding, extra space added here if needed
        for (int j = 0; j < line.size(); j++) {
            newLine += line[j];
            if (j < spaceBetweenWords) { // Don't add a space after the last word
                newLine += ' '; // Space between words
            }
        }
        newLine += string(padding, ' '); //right padding

        result.push_back(newLine);
    }
    return result;
}

// c2 function
void print(vector<string> list) {
    for (int i = 0; i < list.size(); i++) {
            cout << list[i] << endl;
    }
}
void reversePrint(vector<string> list) {
    for (int i = 0; i < list.size(); i++){
            cout << list[list.size() - 1 - i] << endl;
    }
}
void fnordPrint(vector<string> list) {
    for (int i = 0; i < list.size(); i++) {
        if (list[i].find("fnord") < list[i].size()) {  // Is a real/valif index
            cout << list[i] << endl;
        }
    }
}

int main() {
    int N;
    string c1, c2;
    cin >> N >> c1 >> c2;
    
    if (N <= 0) {
        cerr << "Error, line length must be positive." << endl;
        return 1;
    } 
    if ((c1 != "rr" && c1 != "j" && c1 != "rl" && c1 != "c") || (c2 != "f" && c2 != "r" && c2 != "g")) {
        cerr << "Error, command is illegal." << endl;
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

    // Function calls with c1
    vector<string> result;
    if (c1 == "rr") {
        result = raggedRight(list, N);
    } else if (c1 == "j") {
        result = justify(list, N);
    } else if (c1 == "rl") {
        result = raggedLeft(list, N);
    } else if(c1 == "c"){
        result = centre(list, N);
    }


    // Function calls with c2
    if (c2 == "f") {
        print(result);
    } else if (c2 == "r"){
        reversePrint(result);
    } else if (c2 == "g") {
        fnordPrint(result);
    }

    return 0;
}