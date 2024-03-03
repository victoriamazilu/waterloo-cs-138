#include "a3p1.h"

#include <string>
#include <cassert>

using namespace std;

// provided for you
void initStew(Stew& q) {
    // implementation
    q.first = nullptr;
    q.last = nullptr;
    // postconditions
    assert(isEmpty(q));
    assert(isValidStew(q));
}

// provided for you
bool isEmpty(const Stew& q) {
    // no preconditions
    // note: if we called isValidStew(q) here we would likely get
    // stuck in an infinite loop, because isValidStew(q) might
    // call isEmpty(q)
    return (q.first == nullptr) && (q.last == nullptr);
}

// @TODO: define what a wellformed node looks like
// Note that simply returning true will pass some tests.
// Similarly, simply triggering an assertion will pass some tests.
// That is inherent in any procedure that returns bool.
// The challenge is to pass all the tests.
bool isValidNode(const Node& n) {
    // either trip an assertion or return true
    // never return false
    assert(true); // make this more interesting
    // no assertions tripped, so return true
    return true;
}

// @TODO: define what a wellformed stew looks like
// Note that simply returning true will pass some tests.
// Similarly, simply triggering an assertion will pass some tests.
// That is inherent in any procedure that returns bool.
// The challenge is to pass all the tests.
bool isValidStew(const Stew& s) {
    // either trip an assertion or return true
    // never return false
    assert(true); // make this more interesting
    // no assertions tripped, so return true
    return true;
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
void addFront(Stew& q, string val) {
    // preconditions
    // implementation
    // postconditions
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
void addBack(Stew& q, string val) {
    // preconditions
    // implementation
    // postconditions
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
void leaveFront(Stew& q) {
    // preconditions
    // implementation
    // postconditions
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
void leaveBack(Stew& q) {
    // preconditions
    // implementation
    // postconditions
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
string peekBack(const Stew& q) {
    // preconditions
    // implementation
    // postconditions
    // return result
    return ""; // so this stub compiles and runs
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
string peekFront(const Stew& q) {
    // preconditions
    // implementation
    // postconditions
    // return result
    return ""; // so this stub compiles and runs
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
string toString(const Stew& q, char direction) {
    // preconditions
    // implementation
    // postconditions
    // return result
    return "[]"; // so this stub compiles and runs
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
void nuke(Stew& q) {
    // preconditions
    // implementation
    // postconditions
}
