#include <iostream>
#include <string>
#include <cctype> // for tolower()
#include <map>
#include <cassert>
#include "a5p2.h"

using namespace std;
    
LexTree::LexTree() : isWord(false) {
}

LexTree::~LexTree() {
    deleteChildren(this);
}

void LexTree::deleteChildren(LexTree* node) {
    if (node == nullptr) {
        return;
    }
    while (!node->children.empty()) {
        auto it = node->children.begin();
        auto to_delete = it->second;
        node->children.erase(it);
        deleteChildren(to_delete);
        delete to_delete;
    }
}

bool LexTree::isValidNode(const LexTree* node) const {
    if (node->children.empty()) {
        assert(node->isWord); 
    }

    for (const auto& child : node->children) {
        assert(islower(child.first)); 

        if (!isValidNode(child.second)) {
            return false;
        }
    }
    return true;
}

bool LexTree::isValid() const {
    if (children.empty()) {
        return true;
    }

    return isValidNode(this);
}

void LexTree::addWord(const string& s) {
    assert(isValid());

    LexTree* current = this;
    for (char ch : s) {
        ch = tolower(ch); 
        if (current->children.find(ch) == current->children.end()) {
            current->children[ch] = new LexTree();
        }
        current = current->children[ch];
    }
    current->isWord = true; 

    assert(isValid());
}

bool LexTree::hasWord(const string& s) const {
    assert(isValid()); 
    
    const LexTree* currentNode = this;
    for (char ch : s) {
        ch = tolower(ch);
        if (currentNode->children.count(ch) == 0) {
            return false;
        }
        currentNode = currentNode->children.at(ch);
    }
    
    return currentNode->isWord;
}

void gatherWords(const LexTree* node, const string& prefix, vector<string>& words) {
    if (node->getIsWord()) {
        words.push_back(prefix);
    }
    for (const auto& child : node->getChildren()) {
        gatherWords(child.second, prefix + child.first, words);
    }
}



