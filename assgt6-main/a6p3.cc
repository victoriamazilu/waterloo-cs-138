#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "HashTable.h"
#include "a6p1.h"
#include "a6p2.h"
#include "a6p3.h"

using namespace std;

// Ancillary function for powerset.  It adds a character onto the beginning
// of each string in a vector.
vector<string> addChar(const vector<string>& v, char c) {
    vector<string> ans;
    for (int i=0; i<(int)v.size() ; i++) {
		    ans.push_back(c + v.at(i));
    }
    return ans;
}

// This takes a string and returns the power(multi)set of its characters
// as a vector.  For example, powerset of "aab" would be the vector with
// elements (in no particular order): "aab" "ab" "aa" "a" "ab" "a" "b".
// Assume we don't care about eliminating duplicates for now.
vector<string> powerset(string s) {
    vector<string> ans;
    if (s.size() == 0) {
		    ans.push_back("");
    } else {
        char c = s.at(0);
        string rest = s.substr(1);
        vector<string> psetRest = powerset (rest);
        ans = addChar (psetRest, c);
        ans.insert(ans.end(), psetRest.begin(), psetRest.end());
    }
    return ans;
}

// TODO - Implement the two overloads of scrabbleValue()
int scrabbleValue(char c) {
    if (!isalpha(c)) {
        cerr << "Error: Received non-alphabetical character '" << c << "'" << endl;
        assert(false); 
    }

    c = tolower(c);

    if (c == 'a' || c == 'e' || c == 'i' || c == 'l' || c == 'n' || c == 'o' || c == 'r' || c == 's' || c == 't' || c == 'u') {
        return 1;
    } else if (c == 'd' || c == 'g') {
        return 2;
    } else if (c == 'b' || c == 'c' || c == 'm' || c == 'p') {
        return 3;
    } else if (c == 'f' || c == 'h' || c == 'v' || c == 'w' || c == 'y') {
        return 4;
    } else if (c == 'k') {
        return 5;
    } else if (c == 'j' || c == 'x') {
        return 8;
    } else { 
        return 10;
    }
}

int scrabbleValue(string s) {
    int sum = 0;
    for (char c : s) {
        sum += scrabbleValue(c);  
    } 
    return sum;
}

string bestScrabbleWord(string letters) {
    for (char l : letters) {
        if (!isalpha(l)) {
            cerr << "Error: Received non-alphabetical character '" << l << "'" << endl;
            assert(false);
        }
    } 

    // HashTable to check if the word is a valid Scrabble word
    SimpleHashTable validWords;
    ifstream file("twl-words.txt");
    validWords.insert(file);
    string result = "";

    map<int, string> validScrabbleWords;
    vector<string> allWords = powerset(letters);

    int maxLength = -1;

    for (const string& word : allWords) {
        // Convert word to lowercase in order to use lookup
        string wordLC = word;
        transform(wordLC.begin(), wordLC.end(), wordLC.begin(), ::tolower);

        // If the value has a higher scrabble value and is a valid word then set it as the result
        if (scrabbleValue(word) > maxLength && validWords.lookup(wordLC)) {
            maxLength = scrabbleValue(word);
            result = word;
        }
    }

    return result;
}
