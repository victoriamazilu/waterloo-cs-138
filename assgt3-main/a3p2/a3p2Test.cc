#include "a3p2.h"
#include "gtest/gtest.h"

using namespace std;

/* ************************************************************** */
/* Chunky Stack Validity                                          */
/* ************************************************************** */

TEST(StackForm, ChunkSizeAboveZero) {
    Stack s;
    s.chunkSize  = -1;
    EXPECT_DEATH(isValidStack(s), "");
}

TEST(StackForm, TopEltGreaterThanChunkSize) {
    Stack s;
    s.chunkSize = 1;
    s.topElt = 2;
    EXPECT_DEATH(isValidStack(s), "");
}

TEST(StackForm, EmptyStackWithBadTopElt) {
    Stack s;
    s.firstChunk = nullptr;
    s.topElt = 1; // this should be -1 for an empty stack
    EXPECT_TRUE(isEmpty(s)); 
    EXPECT_DEATH(isValidStack(s), "");
}

TEST(StackForm, StackCannotStoreSpecialUnusedSlotValue) {
    Stack s;
    initStack(1, s);
    s.firstChunk = createNewNodeChunk(1);
    s.topElt = 0;
    s.firstChunk->val[0] = "alpha";
    EXPECT_FALSE(isEmpty(s)); 
    EXPECT_TRUE(isValidStack(s));
    // wellformed so far, now mess it up
    s.firstChunk->val[0] = UNUSED_SLOT;
    EXPECT_DEATH(isValidStack(s), "");
    delete[] s.firstChunk->val;
    delete s.firstChunk;
}

TEST(StackForm, UnusedStackSlotsShouldNotHaveGhostValues) {
    Stack s;
    initStack(5, s);
    s.firstChunk = createNewNodeChunk(5);
    s.topElt = 2;
    s.firstChunk->val[s.topElt+1] = "ghost value should not be here";
    EXPECT_FALSE(isEmpty(s)); 
    EXPECT_DEATH(isValidStack(s), "");
    delete[] s.firstChunk->val;
    delete s.firstChunk;
}

TEST(StackForm, SubsequentChunkShouldNotHaveUnusedSlots) {
    Stack s;
    initStack(1, s);
    s.topElt = 0;
    s.firstChunk = createNewNodeChunk(1);
    s.firstChunk->val[0] = "beta";
    s.firstChunk->next = createNewNodeChunk(1);
    s.firstChunk->next->val[0] = "alpha";
    EXPECT_FALSE(isEmpty(s)); 
    EXPECT_TRUE(isValidStack(s));
    // wellformed so far
    // now we break it
    s.firstChunk->next->val[0] = UNUSED_SLOT;
    EXPECT_DEATH(isValidStack(s), "");
    delete[] s.firstChunk->next->val;
    delete s.firstChunk->next;
    delete[] s.firstChunk->val;
    delete s.firstChunk;
}


/* ************************************************************** */
/* End-to-end testing                                             */
/* ************************************************************** */

TEST(EndToEnd, GivenOneItemIsPushedTheSameItemExpectedAtTop) {
    Stack s;
    initStack (3,s);
    
    string expected = "alpha";
    push(expected, s);
    EXPECT_EQ(expected, top(s));

    nuke(s);
}

TEST(EndToEnd, GivenTwoPushedElementsTheSecondItemExpectedAtTop) {
    Stack s;
    initStack (3,s);
    push("alpha", s);

    string expected = "beta";
    push(expected, s);

    EXPECT_EQ(expected, top(s));

    nuke(s);
}

TEST(EndToEnd, GivenTwoPushedElementsCombinationOfTheseTwoIsExpectedFromToString) {
    Stack s;
    initStack (3,s);
    push("alpha", s);
    push("beta", s);

    string expected = "[beta, alpha]";
    EXPECT_EQ(expected, toString(s));

    nuke(s);
}

TEST(EndToEnd, GivenTwoPushedElementsWhenPopIsInvokedSecondOneExpectedToRemain) {
    Stack s;
    initStack (3,s);
    push("alpha", s);
    push("beta", s);
    pop(s);

    string expected = "alpha";
    EXPECT_EQ(expected, top(s));

    nuke(s);
}

TEST(EndToEnd, GivenTwoPushedElementsTheSizeOfTwoIsExpected) {
    Stack s;
    initStack (3,s);

    push("alpha", s);
    push("beta", s);

    EXPECT_EQ(2, size(s));

    nuke(s);
}

TEST(EndToEnd, GivenTwoPushedElementsWhenSwapIsInvokedSwappedItemsExpectedFromToString) {
    Stack s;
    initStack (3,s);

    push("alpha", s);
    push("beta", s);

    swap(s);

    string expected = "[alpha, beta]";
    EXPECT_EQ(expected, toString(s));

    nuke(s);
}




/* ************************************************************** */
/* New Tests                                                      */
/* ************************************************************** */

TEST(EndToEnd, PushToFillMultipleChunks) {
    Stack s;
    initStack(2, s);
    
    push("alpha", s);
    push("beta", s);
    push("gamma", s); // Should create and move to a new chunk

    string expected = "[gamma, beta, alpha]";
    EXPECT_EQ(expected, toString(s));

    nuke(s);
}

// Test boundary condition when last element in a chunk is popped
TEST(EndToEnd, PopLastElementInChunk) {
    Stack s;
    initStack(2, s);
    
    push("alpha", s);
    push("beta", s);
    pop(s);

    string expected = "alpha";
    EXPECT_EQ(expected, top(s));

    nuke(s);
}

TEST(EndToEnd, SizeAfterPushPopOperations) {
    Stack s;
    initStack(3, s);

    push("alpha", s);
    push("beta", s);
    push("gamma", s);
    pop(s);
    push("delta", s);

    EXPECT_EQ(3, size(s)); // Should be 3 elements in the stack

    nuke(s);
}

// Test swap on stack with only one element should assert
TEST(EndToEnd, SwapWithSingleElementShouldAssert) {
    Stack s;
    initStack(3, s);

    push("alpha", s);

    EXPECT_DEATH(swap(s), "");

    nuke(s);
}

// Test swap on an empty stack should assert
TEST(EndToEnd, SwapOnEmptyStackShouldAssert) {
    Stack s;
    initStack(3, s);

    EXPECT_DEATH(swap(s), "");

    nuke(s);
}

// Test toString on an empty stack
TEST(EndToEnd, ToStringOnEmptyStack) {
    Stack s;
    initStack(3, s);

    string expected = "[]";
    EXPECT_EQ(expected, toString(s));

    nuke(s);
}

// Test top on an empty stack should assert
TEST(EndToEnd, TopOnEmptyStackShouldAssert) {
    Stack s;
    initStack(3, s);

    EXPECT_DEATH(top(s), "");

    nuke(s);
}

// Test pop on an empty stack should assert
TEST(EndToEnd, PopOnEmptyStackShouldAssert) {
    Stack s;
    initStack(3, s);

    EXPECT_DEATH(pop(s), "");

    nuke(s);
}

TEST(EndToEnd, PoppingElementsRemovesChunk) {
    Stack s;
    initStack(2, s); 
    
    push("alpha", s);
    push("beta", s);
    push("gamma", s);
    pop(s); // Should remove "gamma" and delete the second chunk

    string expected = "[beta, alpha]";
    EXPECT_EQ(expected, toString(s));

    nuke(s);
}