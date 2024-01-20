#include <iostream>
using namespace std;
#include <vector>

void print( vector<string> lines){
    for (int i = 0; i < lines.size(); i++){
        cout << lines[i] << endl;
    }
}

int main(){
    int N;
    string token;
    vector<string> words;
    vector<string> lines; // vector to store output
    string currentLine = ""; // current line: starts empty

    cin >> N;

    if (N <= 0) {
        cerr << "Error, line length must be positive." << endl;
        return 1;
    }

    cin.ignore();
    
    while(cin>>token){
        if (token.size()>N){ //cut it off if too long 
            words.push_back(token.substr(0,N));
        }
        else{
            words.push_back(token); // just add 
        }
    }



    for (int i = 0; i < words.size(); i++) { // iterating through each word in words vector
        if (currentLine.size() + words[i].size() + (currentLine.size() > 0) <= N) { // if theres space, execute
            if(currentLine.size() > 0){ // if not empty, add space and word
                currentLine += " ";
            }
            currentLine += words[i];
        } else{ // if theres no space left, execute
            lines.push_back(currentLine); // push it to output 
            currentLine = words[i]; //reset 
        }
    }
    if (!currentLine.empty()) { // this adds the remaining words to output even though they havent reached max`
        lines.push_back(currentLine);
    }

    // for (int i = 0; i < lines.size(); i++) {
    //     int spacesNeeded = N - lines[i].length();
    //     if (lines[i].length() < N) {
    //         lines[i] = lines[i] + string(spacesNeeded, ' ');
    //     }
    // }

    print(lines);
}