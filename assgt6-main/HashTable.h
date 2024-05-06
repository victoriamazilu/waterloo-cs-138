/* ************************************************************** */
/*                     DO NOT MODIFY THIS FILE                    */
/* ************************************************************** */
#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <string>
#include <vector>
#include <fstream>

class HashTable {
    public:
        HashTable();
        HashTable(int K);
        virtual ~HashTable();
        void insert(std::string word);
        void insert(std::ifstream& file); // You implement this
        void remove(std::string word);	// You implement this too
        bool lookup(std::string word) const;
        std::string toString() const;
        void report() const;
        static const int DefaultSize = 1000;
    protected: 
	    int getTableSize() const;
        struct Node {
            std::string word;
            Node* next;
        };    
    private: 
	    std::vector<Node*> table;
        // The "hash" function will be defined by each child class, 
        // each one using a different strategy.  But it needs to be
        // abstract (aka "pure virtual") in the abstract parent class.
        virtual int hash(std::string key) const = 0;
};

#endif
