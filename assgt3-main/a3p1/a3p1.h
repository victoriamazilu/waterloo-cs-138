#include <string>

struct Node {
    std::string val;
    Node* next;
    Node* prev;
};

struct Stew {
    Node* first;
    Node* last;
};

bool isValidStew(const Stew& s);
bool isValidNode(const Node& n);

void initStew(Stew& q);
bool isEmpty(const Stew& q);

void addFront(Stew& q, std::string val);
void addBack(Stew& q, std::string val);

void leaveFront(Stew& q);
void leaveBack(Stew& q);

std::string peekBack(const Stew& q);
std::string peekFront(const Stew& q);

std::string toString(const Stew& q, char direction);

void nuke(Stew& q);
