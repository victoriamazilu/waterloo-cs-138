#include "gtest/gtest.h"
#include "a4p2.h"

using namespace std;

/* ************************************************************** */
/* Tests for Assignment 4 Part 2                                  */
/* ************************************************************** */
// By default this file contains exact copies of all the Marmoset
// public tests in a4p2c.

// Currently these tests achieve 58% coverage on the staff solution.
// To pass a4p2t you will need to augment them to achieve at lest 
// 90% coverage on our solution (though, as usual, 100% coverage is
// possible).

// Note: All the other BST functions in the staff solution (besided
// nuke and remove) were transfered to another file so that they are
// ignored by gcov. a4p2t checks your test coverage on BST_remove
// and BST_nuke ONLY.

TEST(removePub, givenEmptyBSTExpectRemoveDies) {
    BST bst;
    BST_init(bst);
    EXPECT_DEATH(BST_remove(bst, "thisStringIsATest"), "Error, couldn't find \"thisStringIsATest\" in the BST");
}

TEST(removePub, givenOneElementBSTExpectRemovingThatElementLeavesBSTEmpty) {
    BST bst;
    BST_init(bst);
    BST_insert(bst, "alpha");
    BST_remove(bst, "alpha");
    EXPECT_TRUE(BST_isEmpty(bst));
}

TEST(nukePub, givenEmptyBSTExpectNukeDoesNothing) {
    BST bst;
    BST_init(bst);
    BST_nuke(bst);
}

TEST(nukePub, givenOneElementBSTExpectNukeCleansUp) {
    BST bst;
    BST_init(bst);
    BST_insert(bst, "alpha");
    BST_nuke(bst);
}

/* ************************************************************** */
/* MORE TESTS HERE                                                */
/* ************************************************************** */
TEST(removePub, givenBSTWithTwoChildrenExpectProperRemovalAndBSTPropertyMaintained) {
    BST bst;
    BST_init(bst);
    BST_insert(bst, "parent");
    BST_insert(bst, "leftChild");
    BST_insert(bst, "rightChild");
    BST_remove(bst, "parent");
    EXPECT_FALSE(BST_has(bst, "parent"));
    EXPECT_TRUE(BST_has(bst, "leftChild"));
    EXPECT_TRUE(BST_has(bst, "rightChild"));
    BST_nuke(bst);
}

TEST(removePub, givenBSTWithLeftChildOnlyExpectProperRemoval) {
    BST bst;
    BST_init(bst);
    BST_insert(bst, "parent");
    BST_insert(bst, "leftChild");
    BST_remove(bst, "parent");
    EXPECT_FALSE(BST_has(bst, "parent"));
    EXPECT_TRUE(BST_has(bst, "leftChild"));
    BST_nuke(bst);
}

TEST(removePub, givenBSTWithRightChildOnlyExpectProperRemoval) {
    BST bst;
    BST_init(bst);
    BST_insert(bst, "parent");
    BST_insert(bst, "rightChild");
    BST_remove(bst, "parent");
    EXPECT_FALSE(BST_has(bst, "parent"));
    EXPECT_TRUE(BST_has(bst, "rightChild"));
    BST_nuke(bst);
}

TEST(nukePub, givenMultipleElementBSTExpectProperNuke) {
    BST bst;
    BST_init(bst);
    BST_insert(bst, "alpha");
    BST_insert(bst, "beta");
    BST_insert(bst, "gamma");
    BST_nuke(bst);
    EXPECT_TRUE(BST_isEmpty(bst));
}

TEST(removePub, givenComplexNode) {
    BST bst;
    BST_init(bst);
    BST_insert(bst, "d");
    BST_insert(bst, "b");
    BST_insert(bst, "a"); 
    BST_insert(bst, "c"); 
    BST_insert(bst, "f"); 
    BST_insert(bst, "e");
    BST_insert(bst, "g");

    BST_remove(bst, "d");
    BST_remove(bst, "g");
    BST_remove(bst, "c");

    EXPECT_FALSE(BST_has(bst, "d"));
    EXPECT_TRUE(BST_has(bst, "b"));
    EXPECT_FALSE(BST_has(bst, "c"));
    EXPECT_TRUE(BST_has(bst, "f"));
    BST_nuke(bst);
}

