#include <string>

#define UNUSED_SLOT "__UNUSED_SLOT__"

struct NodeChunk {
    std::string* val; // WARNING: this is used as a pointer to an array of strings
    NodeChunk* next;
};

struct Stack {
    NodeChunk* firstChunk;
    int topElt;
    int chunkSize; // conceptually const, but compiler complains
};

bool isValidStack(const Stack& s);

NodeChunk* createNewNodeChunk(const int chunkSize);
void initStack(const int chunkSize, Stack& s);

bool isEmpty(const Stack& s);

void push(const std::string v, Stack& s);
void pop(Stack& s);
void swap(Stack& s);

int size(const Stack& s);

std::string top(const Stack& s);
std::string toString(const Stack& s);

void nuke(Stack& s);
