#include "a3p1.h"

#include <string>
#include <cassert>

using namespace std;

// provided for you
void initStew(Stew& q) {
    // no preconditions
    // implementation
    q.first = nullptr;
    q.last = nullptr;
    // postconditions
    assert(isEmpty(q));
    assert(isValidStew(q));
}

// provided for you
bool isEmpty(const Stew& q) {
    return (q.first == nullptr) && (q.last == nullptr);
}

bool isValidNode(const Node& n) {
    assert(n.next != &n && n.prev != &n);               // no self cycles
    if(n.next != nullptr){
        assert(n.next !=  n.prev);     // no loops
    }
    return true;
}

bool isValidStew(const Stew& s) {
    if (isEmpty(s)) {
        assert(s.first == nullptr && s.last == nullptr);
        return true;
    }

    // If the stew is not empty, then neither first or last should be nullptr.
    assert(s.first != nullptr && s.last != nullptr); 

    Node* cur = s.first;
    Node* prev = nullptr;
    while (cur != nullptr) {
        assert(isValidNode(*cur));

        // Check that the backwards link is correct
        assert(cur->prev == prev);
        prev = cur;
        cur = cur->next;
    }

    assert(prev == s.last);

    if (s.first != s.last) {
        assert(s.first->prev == nullptr && s.last->next == nullptr);
    }

    // no assertions tripped, so return true
    return true;
}


// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
void addFront(Stew& q, string val) {
        // preconditions
        assert(val != "");
        assert(isValidStew(q)); // The stew must be valid before we can add to it

        // implementation
        Node* newNode = new Node;
        newNode -> val = val;
        newNode -> prev = nullptr;
        newNode -> next = q.first;

        if (q.first != nullptr) {
            q.first -> prev = newNode;
            q.first = newNode;
        } else {
            q.first = newNode;
            q.last = newNode;
        }

        // postconditions
        assert(isValidStew(q)); // The stew must be valid after we add to it.
        assert(!isEmpty(q));
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
void addBack(Stew& q, string val) {
    // preconditions
    assert(val != "");
    assert(isValidStew(q));

    // implementation
    Node* newNode = new Node;
    newNode -> val = val;
    newNode -> prev = q.last;
    newNode -> next = nullptr;

    if (q.last != nullptr) {
        q.last -> next = newNode;
        q.last = newNode;
    } else {
        q.first = newNode;
        q.last = newNode;
    }

    // postconditions
    assert(isValidStew(q));
    assert(!isEmpty(q));
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
void leaveFront(Stew& q) {
    // preconditions
    assert(!isEmpty(q));
    assert(isValidStew(q));

    // implementation
    Node* toDelete = q.first;

    if(toDelete -> next != nullptr){
        q.first = toDelete -> next;
        q.first -> prev = nullptr;

        if(q.first -> next == nullptr){
            q.last = q.first;
        }

    } else {
        q.first = nullptr;
        q.last = nullptr;
    }
    
    delete toDelete; 

    // postconditions
    assert(isValidStew(q));
    if (q.first == q.last && q.first == nullptr) {
        assert(isEmpty(q));
    }
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
void leaveBack(Stew& q) {
    // preconditions
    assert(!isEmpty(q));
    assert(isValidStew(q));

    // implementation
    Node* toDelete = q.last;

    if(toDelete -> prev != nullptr){
        q.last = toDelete -> prev;
        q.last -> next = nullptr;

        if(q.last -> prev == nullptr){
            q.first = q.last;
        }

    } else {
        q.first = nullptr;
        q.last = nullptr;
    }
    
    delete toDelete; 

    // postconditions
    assert(isValidStew(q));
    if (q.first == q.last && q.first == nullptr) {
        assert(isEmpty(q));
    }
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
string peekBack(const Stew& q) {
    // preconditions
    assert(!isEmpty(q));
    assert(isValidStew(q));

    // implementation
    string result = q.last -> val;

    // postconditions
    assert(isValidStew(q));

    return result;
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
string peekFront(const Stew& q) {
    // preconditions
    assert(!isEmpty(q));
    assert(isValidStew(q));

    // implementation
    string result = q.first -> val;

    // postconditions
    assert(isValidStew(q));

    return result;
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
string toString(const Stew& q, char direction) {
    // preconditions
    assert(isValidStew(q));

    // implementation
    string result = "[";

    if(isEmpty(q) && (direction == 'f' || direction == 'r')){
        return "[]";
    }

    if (direction == 'f') {
        Node* cur = q.first;
        while(cur != nullptr){
            result += cur -> val;
            if(cur -> next != nullptr){
                result += ", ";
            }
            cur = cur -> next;
        }
    } else if (direction == 'r') {
        Node* cur = q.last;
        while(cur != nullptr){
            result += cur -> val;
            if(cur -> prev != nullptr){
                result += ", ";
            }
            cur = cur -> prev;
        }
    } else {
        // If direction is not 'f' or 'r', return an error message
        result = "Error, illegal direction: (";
        result += direction;
        result += ")";
        return result;
    }

    // postconditions
    assert(isValidStew(q));

    return result + "]"; 
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
void nuke(Stew& q) {
    // preconditions
    assert(isValidStew(q));

    // implementation
    Node* current = q.first;
    Node* toDelete = nullptr;

    while (current != nullptr) {
        toDelete = current;
        current = current->next;

        // Check if the node to delete is the last one
        if (toDelete == q.last) {
            q.last = nullptr; 
        }

        delete toDelete;
        toDelete = nullptr;

        // If we have more nodes to delete, prepare the next node's previous pointer
        if (current != nullptr) {
            current->prev = nullptr;
        }
    }

    q.first = nullptr;

    // Postconditions
    assert(isEmpty(q));
    assert(isValidStew(q));
}

