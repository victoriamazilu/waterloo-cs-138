#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include "a4p3.h"
using namespace std;

//////////////// previous functions for simplicity ////////////////
void Q_init (Queue& q) {
    q.first = nullptr;
    q.last = nullptr;
}

bool Q_isEmpty (const Queue& q) {
    return nullptr == q.first;
}

void Q_enter (Queue& q, SBLnode* newNode) { 
    newNode -> next = nullptr;
    if (Q_isEmpty(q)) {
        q.first = newNode;
    } else {
        q.last -> next = newNode;
    }
    q.last = newNode;
}

string Q_first (const Queue& q) { 
    assert(!Q_isEmpty(q));
    return q.first -> name;
}

void Q_leave (Queue& q) {
    assert(!Q_isEmpty(q));
    q.first = q.first -> next;
    if(nullptr == q.first) {
        q.last = nullptr;
    }
}

void Q_nuke (Queue& q) {
    while(!Q_isEmpty(q)) {
        Q_leave(q);
    }
} 

void BST_init (BST& root) {
    root = nullptr;
}

bool BST_isEmpty (const BST& root) {
    return nullptr == root;
}

bool BST_has (const BST& root, std::string name) {
    if (nullptr == root) {
	    return false;
    } else if (root->name == name) {
	    return true;
    } else if (root->name > name) {
	    return BST_has (root->left, name);
    } else {
	    return BST_has (root->right, name);
    }
}

void BST_insert (BST& root, SBLnode* node) {
    if (root == nullptr) {
        root = node; 
    } else if (node->name < root->name) {
        BST_insert(root->left, node);
    } else if (node->name > root->name) {
        BST_insert(root->right, node);
    } 
}

void BST_print (const BST& root) {
    if (nullptr != root) {
        BST_print (root->left);
        cout << root->name << endl;
        BST_print (root->right);
    }
}

BST& findNextNode(BST& root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

// Recurvsive helper
// BST_Node* BST_removeRecHelper(BST_Node* root, const string& name) {
//     if (root == nullptr) {
//         return nullptr;
//     } else if (name < root->name) { // name in the left subtree
//         root->left = BST_removeRecHelper(root->left, name);
//     } else if (name > root->name) { // name in the right subtree
//         root->right = BST_removeRecHelper(root->right, name);
//     } else { // name found
//         if (root->left == nullptr && root->right == nullptr) { // Case 1: No children
//             delete root;
//             root = nullptr;
//         } 
//         // Case 2: One child
//         else if (root->left == nullptr) { 
//             BST_Node* temp = root;
//             root = root->right;
//             delete temp;
//         } else if (root->right == nullptr) {
//             BST_Node* temp = root;
//             root = root->left;
//             delete temp;
//         } 
//         // Case 3: Two children
//         else { 
//             BST_Node* temp = root;
//             BST_Node* replacement = findNextNode(root->right);
//             replacement->left = root->left;
//             root = replacement;
//             delete temp;
//         }
//     }
//     return root;
// }

BST_Node* BST_removeRecHelper(BST_Node* root, const string& name) {
    if (root == nullptr) {
        return nullptr;
    } else if (name < root->name) { // name in the left subtree
        root->left = BST_removeRecHelper(root->left, name);
    } else if (name > root->name) { // name in the right subtree
        root->right = BST_removeRecHelper(root->right, name);
    } else { // name found
        if (root->left == nullptr && root->right == nullptr) { // Case 1: No children
            delete root;
            root = nullptr;
        } 
        else if (root->left == nullptr) { // Case 2: One child
            BST_Node* temp = root;
            root = root->right;
            delete temp;
        } else if (root->right == nullptr) {
            BST_Node* temp = root;
            root = root->left;
            delete temp;
        } 
        else { // Case 3: Two children
            BST_Node* temp = root->left;
            // Then go as far right as possible
            BST_Node* temp2 = nullptr;
            while (temp->right != nullptr) {
                temp2 = temp;
                temp = temp->right;
            }
            // If the replacement is not the immediate left child
            if (temp2 != nullptr) {
                temp2->right = temp->left;
                temp->left = root->left;
            }
            temp->right = root->right;
            delete root;
            root = temp;
        }
    }
    return root;
}

void BST_remove (BST& root, string name) { 
    if (root == nullptr || !BST_has(root, name)) {
        cerr << "Error, couldn't find \"" << name << "\" in the BST\n";
        exit(1);
    }
    root = BST_removeRecHelper(root, name);
}

void BST_nuke (BST & root) {
    if (root != nullptr) {
        if (root->left != nullptr) {
            BST_nuke(root->left);
        }
        if (root->right != nullptr) {
            BST_nuke(root->right);
        }
        delete root;
        root = nullptr;
    }
}

void BST_toVector(const BST& root, std::vector<std::string>& elements) {
    if (root != nullptr) {
        BST_toVector(root->left, elements);
        elements.push_back(root->name);
        BST_toVector(root->right, elements);
    }
}
///////////////////////////////////////////////////////////////////


void SBL_init (SBL& sbl) {
    sbl.q.first = nullptr;
    sbl.q.last = nullptr;
    sbl.root = nullptr;
    sbl.numElts = 0;
} 

int SBL_size (const SBL& sbl){
    return sbl.numElts;
} 

void SBL_arrive (SBL& sbl, std::string name) {
    SBLnode* newNode = new SBLnode{name, nullptr, nullptr, nullptr};
    
    BST_insert(sbl.root, newNode);
    Q_enter(sbl.q, newNode);

    sbl.numElts++;
} 

void SBL_leave (SBL& sbl) { 
    if (sbl.numElts <= 0) {
        cerr << "Error, SBL is empty." << endl;
        exit(1);
    }

    string nameToRemove = Q_first(sbl.q);
    Q_leave(sbl.q);
    BST_remove(sbl.root, nameToRemove); 

    sbl.numElts--;
}

std::string SBL_first (const SBL& sbl) { 
    if (sbl.numElts <= 0) {
        cerr << "Error, SBL is empty." << endl;
        exit(1);
    }

    return sbl.q.first->name;
} 

bool SBL_has (const SBL& sbl, std::string name) {
    return BST_has(sbl.root, name);
} 

std::string SBL_toArrivalOrderString (const SBL& sbl) {
    std::string result = "[";
    SBLnode* current = sbl.q.first;
    while (current != nullptr) {
        result += current->name;
        if (current->next != nullptr) {
            result += ", ";
        }
        current = current->next;
    }
    result += "]";
    return result;
}
std::string SBL_toLexicographicalOrderString (const SBL& sbl) {
    string result = "[";
    vector<string> elements;
    BST_toVector(sbl.root, elements);
    for (size_t i = 0; i < elements.size(); ++i) {
        result += elements[i];
        if (i + 1 < elements.size()) {
            result += ", ";
        }
    }
    result += "]";
    return result;
}

void SBL_nuke (SBL& sbl) {
    Q_nuke(sbl.q);
    BST_nuke(sbl.root);
    
    sbl.numElts = 0;
}


