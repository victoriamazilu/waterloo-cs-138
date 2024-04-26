/* ************************************************************** */
/*                     DO NOT MODIFY THIS FILE                    */
/* ************************************************************** */
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "HashTable.h"

using namespace std;

// Note that insert/lookup are completely defined here (and call hash) even
// tho hash is not defined here.  This is called the Template Method design
// pattern.  The hash function is private, meaning the children can't call
// it.  However, they can *define* it.  In fact, that's the only difference
// between the children classes: they each provide a different
// implementation of hash!

// Some constructors
HashTable::HashTable() : table{DefaultSize} {}
HashTable::HashTable(int K) : table{(size_t)K} {}

// The destructor has lots of garbage to clean up!  For each bucket with an
// overflow list, we delete the nodes.
HashTable::~HashTable() {
    for (int i=0; i<getTableSize(); i++) {
        Node* p = table.at(i);
        while (nullptr != p) {
            Node* temp = p;
            p = p->next;
            delete temp;
        }
    }
}

// Simple accessor function that will be used by children classes to
// implement the hash function.  It's protected as children need to use it
// but not public as external clients do not need to know about it.
// This is the only information about the table that the children classes
// need to know, so we can make the table itself private!
int HashTable::getTableSize() const {
    return (int) table.size();
}

// Use open hashing with unsorted linked list for overflow.
void HashTable::insert(string key) {
    const int slot = hash(key);
    Node* newNode = new Node;
    newNode->word = key;
    newNode->next = table.at(slot);
    table.at(slot) = newNode;
}

bool HashTable::lookup(string key) const {
    const int slot = hash(key);
    Node* curNode = table.at(slot);
    while (nullptr != curNode) {
        if (curNode->word == key) {
            return true;
        }
	    curNode = curNode -> next;
    }
    return false;
}

// To help you debug, if you find it useful.
string HashTable::toString() const {
    string res;
    for (int i=0; i<getTableSize(); i++) {
        if (nullptr != table.at(i)) {
            res += to_string(i) + ":";
            Node* p = table.at(i);
            while (nullptr != p) {
                res += " " + p->word;
                p = p->next;
            }
            res += "\n";
        }
    }
    return res;
}

// So we can tell how good your hash function is ...
void HashTable::report() const {
    // K is number of buckets
    const int K = getTableSize();
    if (K == 0) {
        cout << "Hash table is empty; nothing to report." << endl;
        return;
    }
    // How many overflow elements in each bucket?
    vector<int> stats (K);
    int totalNumEntries = 0;
    int numNonZeros = 0;
    int maxOverflowSize = 0;
    for (int i=0; i<K ; i++) {
        if (nullptr != table.at(i)) {
            numNonZeros++;
            int numEntriesInThisBucket = 0;
            Node* p = table.at(i);
            while (nullptr != p) {
                p = p->next;
                numEntriesInThisBucket++;
            }
            totalNumEntries += numEntriesInThisBucket;
            if (numEntriesInThisBucket > maxOverflowSize) {
                maxOverflowSize = numEntriesInThisBucket;
            }
            stats.at(i)=numEntriesInThisBucket;
        }
    }
    // This part added 28 March 2014:
    // Compute average # of probes required to establish that an element 
    // is not present by summing the squares of the bucket list lengths, 
    // then dividing by totalNumEntries
    int sumOfSquaresOfBucketListLengths = 0;
    for (int i=0; i<stats.size(); i++) {
	    sumOfSquaresOfBucketListLengths += stats.at(i) * stats.at(i);
    }
    const double avgNumberOfProbes =
        (double) sumOfSquaresOfBucketListLengths / (double) totalNumEntries;
    cout << "Average # of probes to establish an element is not present: " 
	     << setprecision(3) << fixed << avgNumberOfProbes << endl;

    // If we sort, it's trivial to find the median.
    sort(stats.begin(), stats.end());
    const int numEmptyBuckets = K - numNonZeros;
    const int firstNonZeroBucketIndex = numEmptyBuckets;
    cout << "Number of entries in table: " << totalNumEntries << endl;
    cout << "Total # buckets: " << K << " of which " << numEmptyBuckets 
	     << " (" << 100 * numEmptyBuckets / K << "%)" << " were empty."
         << endl;
    // We want the avg and median # of elements, but ignoring the empty
    // buckets, on the grounds that if we're looking for a valid word, it
    // doesn't matter how many empty buckets there are, as we'll be hashing
    // to a non-empty bucket and traversing that list.
    // To compute the median, find the index that is half-way between
    // firstNonZeroBucketIndex and K.
    const int median = stats.at(firstNonZeroBucketIndex + numNonZeros/2);
    const int average = totalNumEntries / numNonZeros;
    cout << "Overflow list length:  Max = " << maxOverflowSize 
	     << "  Median = " << median << "  Average = " << average <<  endl;
}