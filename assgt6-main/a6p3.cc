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
 
}

int scrabbleValue(string s) {

}

string bestScrabbleWord(string letters) {

}
