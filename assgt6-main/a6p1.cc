#include <string>
#include <fstream>
#include "HashTable.h"
#include "a6p1.h"

using namespace std;

void HashTable::remove(string word) {
    int index = hash(word); // Get the bucket index for this word
    Node* current = table[index];
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current -> word != word){
            prev = current;
            current = current->next;
        } else {
            if (prev == nullptr) {
                table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            //prev = current;
            delete current; 
            //delete prev;
            //current = current->next;
            return; 
        }
    }
    // Word not found, no action needed
}

void HashTable::insert(ifstream& file) {
    std::string word;
    while (file >> word) {  
        insert(word); 
    }
}

SimpleHashTable::SimpleHashTable() : HashTable(HashTable::DefaultSize){}

SimpleHashTable::SimpleHashTable(int k) : HashTable(k) {}

SimpleHashTable::~SimpleHashTable() {}


int SimpleHashTable::hash (string key) const {
    int sum = 0;
    for (char c : key) {
        sum += (int)(c); 
    }
    return sum % getTableSize();
}
