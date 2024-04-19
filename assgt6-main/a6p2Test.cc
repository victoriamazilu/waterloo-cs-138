#include <string>
#include <fstream>
#include "gtest/gtest.h"
#include "a6p2.h"

using namespace std;

// By default this file contains copies of the Marmoset tests in
// a6p2c. These tests already achieve 100% coverage on our solution
// so a6p2t will not be worth marks. That said, it still exists if
// you want to use it to check the corectness of your test cases.

// Remember that if you make new whitebox tests for SmartHashTable
// you'll have to add those tests as friends in the class
// declaration in a6p2.h.

TEST(SmartHashTablePub, testConstructorsPub) {
    SmartHashTable ht1; // default constructed talbe
    EXPECT_EQ(ht1.getTableSize(), 1000); // HashTable::DefaultSize == 1000

    for(int i = 1; i < 20; ++i) {
        SmartHashTable ht2{i}; // custom constructed table
        EXPECT_EQ(ht2.getTableSize(), i);
    }
}

TEST(SmartHashTablePub, testThatTheHashFunctionWorks) {
    SmartHashTable ht;
    ht.insert("abc");
    EXPECT_EQ(ht.toString(), to_string(ht.hash("abc")) + ": abc\n");
}

TEST(SmartHashTablePub, printReport) {
    SmartHashTable ht{100000};
    ifstream dictionary{"twl-words.txt"};
    ht.insert(dictionary);
    ht.report();
}
