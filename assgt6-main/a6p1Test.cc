#include <string>
#include "gtest/gtest.h"
#include "a6p1.h"

using namespace std;

// By default this file contains copies of the Marmoset tests in
// a6p1c. Currently they get 75% coverage on our solution. To pass
// the a6p1t coverage test you will need to augment them so that
// they get full coverage (100% lines executed).

// Remember that if you make new whitebox tests for SimpleHashTable
// you'll have to add those tests as friends in the class
// declaration in a6p1.h.

TEST(SimpleHashTablePub, testConstructorsPub) {
    SimpleHashTable ht1; // default constructed talbe
    EXPECT_EQ(ht1.getTableSize(), 1000); // HashTable::DefaultSize == 1000

    for(int i = 1; i < 20; ++i) {
        SimpleHashTable ht2{i}; // custom constructed table
        EXPECT_EQ(ht2.getTableSize(), i);
    }
}

TEST(SimpleHashTablePub, testHashFunctionPub) {
    SimpleHashTable ht;
    EXPECT_EQ(ht.hash("abc"), (int)'a' + (int)'b' + (int)'c');
}

TEST(removePub, testRemoveMissingElementDoesNothing) {
    SimpleHashTable ht;
    ht.insert("one");
    ht.insert("two");
    ht.remove("three");
    string expected = to_string((int)'o' + (int)'n' + (int)'e') + ": one\n" +
                      to_string((int)'t' + (int)'w' + (int)'o') + ": two\n";
    EXPECT_EQ(ht.toString(), expected);
}

TEST(removePub, testRemovingTheOnlyElementLeavesEmptyHT) {
    SimpleHashTable ht;
    ht.insert("one");
    ht.remove("one");
    EXPECT_EQ(ht.toString(), "");
}

TEST(insertPub, testInsertSimpleFile) {
    SimpleHashTable ht;
    ifstream file{"test.txt"};
    ht.insert(file);
    string expected = to_string((int)'o' + (int)'n' + (int)'e') + ": one\n" +
                      to_string((int)'t' + (int)'w' + (int)'o') + ": two\n";
    EXPECT_EQ(ht.toString(), expected);
}

TEST(SimpleHashTablePub, testHashSimpleString) {
    SimpleHashTable ht;
    string key = "abc";
    int expectedHash = 97 + 98 + 99;
    EXPECT_EQ(ht.hash(key), expectedHash);
}

TEST(SimpleHashTablePub, testHashEmptyString) {
    SimpleHashTable ht;
    string key = "";
    int expectedHash = 0;
    EXPECT_EQ(ht.hash(key), expectedHash);
}

TEST(SimpleHashTablePub, testHashCaseSensitivity) {
    SimpleHashTable ht;
    string lowerCase = "abc"; 
    string upperCase = "ABC"; 
    EXPECT_NE(ht.hash(lowerCase), ht.hash(upperCase)); 
}

TEST(simpleHashWithFile, testInsertWithTextFile) {
    SimpleHashTable ht (5);
    ifstream file{"pangram.txt"};
    ht.insert(file);
    ht.remove("dog");
    ht.insert("dog");
}

