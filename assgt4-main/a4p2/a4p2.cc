#include <iostream>
#include <string>
#include <cassert>
#include "a4p2.h"

using namespace std;

// Provided implementations for BST routines

void BST_init (BST& root) {
    root = nullptr;
}

bool BST_isEmpty (const BST& root) {
    return nullptr == root;
}

bool BST_has (const BST& root, std::string key) {
    if (nullptr == root) {
	    return false;
    } else if (root->key == key) {
	    return true;
    } else if (root->key > key) {
	    return BST_has (root->left, key);
    } else {
	    return BST_has (root->right, key);
    }
}

void BST_insert (BST& root, std::string key) {
    if (nullptr == root) {
        root = new BST_Node; 
        root->key = key; 
        root->left = nullptr; 
        root->right = nullptr;
    } else if (key < root->key) {
	    BST_insert(root->left, key);
    } else {
	    BST_insert(root->right, key);
    } 
}

void BST_print (const BST& root) {
    if (nullptr != root) {
        BST_print (root->left);
        cout << root->key << endl;
        BST_print (root->right);
    }
}

BST_Node* findNextNode(BST_Node* root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

// Recurvsive helper
BST_Node* BST_removeRecHelper(BST_Node* root, const string& key) {
    if (root == nullptr) {
        return nullptr;
    } else if (key < root->key) { // Key in the left subtree
        root->left = BST_removeRecHelper(root->left, key);
    } else if (key > root->key) { // Key in the right subtree
        root->right = BST_removeRecHelper(root->right, key);
    } else { // Key found
        if (root->left == nullptr && root->right == nullptr) { // Case 1: No children
            delete root;
            root = nullptr;
        } 
        // Case 2: One child
        else if (root->left == nullptr) { 
            BST_Node* temp = root;
            root = root->right;
            delete temp;
        } else if (root->right == nullptr) {
            BST_Node* temp = root;
            root = root->left;
            delete temp;
        } 
        // Case 3: Two children
        else { 
            // Find smallest in the right subtree
            BST_Node* temp = findNextNode(root->right);
            root->key = temp->key;
            root->right = BST_removeRecHelper(root->right, temp->key);
        }
    }
    return root;
}


void BST_remove (BST& root, string key) { 
    if (root == nullptr || !BST_has(root, key)) {
        cerr << "Error, couldn't find \"" << key << "\" in the BST\n";
        exit(1);
    }
    root = BST_removeRecHelper(root, key);
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
