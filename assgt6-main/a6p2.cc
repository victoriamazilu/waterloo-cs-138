#include <string>
#include "a6p2.h"

using namespace std;

SmartHashTable::SmartHashTable() : HashTable(HashTable::DefaultSize) {}

SmartHashTable::SmartHashTable(int k) : HashTable(k) {}

SmartHashTable::~SmartHashTable() {}

// The following code was inspired by:  http://www.cse.yorku.ca/~oz/hash.html
int SmartHashTable::hash(string key) const {
    unsigned long hash = 5381;
    unsigned int size = key.length();
    unsigned int i = 0;
    for (i = 0; i < size; i++) {

        hash = ((hash << 5) + hash) + (key[i]); /* hash * 33 + c */
    }

    return hash % getTableSize();
}


