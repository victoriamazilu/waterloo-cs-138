// /*
// * CS138, W23, Assignment 1, Problem 1
// * Main Function
// *
// * main function is a special function,
// * which serves as the entry point for the program.
// * 
// * Try to keep it as simple as possible
// * and implement the logic of your program
// * in a1q1.cpp, so that you can write unit tests
// * for them and make sure of their expected behavior.
// */
// #include <iostream>
// #include <string>
// using namespace std;

// // no argc+argv because we aren't using them in A1
// int main() {
//     int N;
//     cin >> N;

//     //check if N is positive
//     if (N <= 0) {
//         cerr << "Error, line length must be positive." << endl;
//         return 1;
//     }
//     cin.ignore();

//     string line;
//     while (getline(cin, line)) {
//         //if the line is longer than N characters, print a substring w/ only the first N characters
//         if (line.length() > N) {
//             cout << line.substr(0, N) << endl;
//         } else { //otherwise print the whole line
//             cout << line << endl;
//         }
//     }

//     return 0;
// }


#include <iostream>
#include <string>
using namespace std;

int main() {
    int N;
    cin >> N;

    if (N <= 0) {
        cerr << "Error, line length must be positive." << endl;
        return 1;
    }

    cin.ignore();

    string line;
    while (getline(cin, line)) {
        if (line.length() > N) {
            cout << line.substr(0, N) << endl;
        } else {
            cout << line << endl;
        }
    }

    return 0;
}
