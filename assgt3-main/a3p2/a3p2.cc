#include "a3p2.h"

#include <string>
#include <cassert>
#include <iostream>

using namespace std;


// provided for you
NodeChunk* createNewNodeChunk(const int chunkSize) {
    // preconditions
    assert(chunkSize > 0);
    // implementation
    NodeChunk* newNodeChunk = new NodeChunk;
    newNodeChunk->next = nullptr;
    newNodeChunk->val = new string[chunkSize];
    // C++ will initialize this array with empty strings
    // we will switch to our special value for unused stack slots
    for (int i=0; i < chunkSize; i++) {
        newNodeChunk->val[i] = UNUSED_SLOT;
    }
    // postconditions
    return newNodeChunk;
}

// provided for you
void initStack(const int chunkSize, Stack& s){
    // preconditions
    assert(chunkSize > 0);
    // implementation
    s.chunkSize = chunkSize;
    s.firstChunk = nullptr;
    s.topElt = -1;
    // postconditions
    assert(isEmpty(s));
    assert(isValidStack(s));
}

// provided for you
bool isEmpty(const Stack& s) {
    // do not call isValidStack() from here
    // because isEmpty() is part of isValidStack()
    return nullptr == s.firstChunk;
}