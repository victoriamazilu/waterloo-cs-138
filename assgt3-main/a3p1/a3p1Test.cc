#include "a3p1.h"
#include "gtest/gtest.h"

using namespace std;

/* ************************************************************** */
/* Stew Unit Tests                                                */
/* ************************************************************** */

/* **** ValidNode Tests ***** */

TEST(IsValidNode, GivenOneValidNodeInvokedIsValidNodeExpectedTrueReturnValue) {
    Node n1;
    n1.next = nullptr;
    n1.prev = nullptr;
    n1.val = "alpha";
    EXPECT_TRUE(isValidNode(n1));
}

TEST(IsValidNode, GivenTwoConnectedNodesInvokedIsValidNodeExpectedTrueReturnValue) {
    Node n1;
    n1.val = "alpha";
    n1.next = nullptr;
    n1.prev = nullptr;
    Node n2;
    n2.val = "beta";
    n2.next = nullptr;
    n2.prev = nullptr;
    // connect n1 and n2 as they might be connected in a Stew
    n1.next = &n2;
    n2.prev = &n1;
    // checks
    EXPECT_TRUE(isValidNode(n1));
    EXPECT_TRUE(isValidNode(n2));
}

TEST(IsValidNode, GivenSelfCycleNodeInNextInvokedIsValidNodeExpectedFalseAssertion) {
    Node n;
    n.val = "alpha";
    n.next = &n;
    n.prev = nullptr;
    EXPECT_DEATH(isValidNode(n), "");
}

TEST(IsValidNode, GivenSelfCycleNodeInPrevInvokedIsValidNodeExpectedFalseAssertion) {
    Node n;
    n.val = "alpha";
    n.prev = &n;
    n.next = nullptr;
    EXPECT_DEATH(isValidNode(n), "");
}

TEST(IsValidNode, GivenNotSimpleGraphInvokedIsValidNodeExpectedFalseAssertion) {
    // create nodes
    Node n1;
    n1.val = "alpha";
    n1.next = nullptr;
    n1.prev = nullptr;
    Node n2;
    n2.val = "beta";
    n2.next = nullptr;
    n2.prev = nullptr;
    // create DAG (malformed)
    n1.prev = &n2;
    n1.next = &n2;
    // should detect this
    EXPECT_DEATH(isValidNode(n1), "");
}

/* **** Valid Stew Tests ***** */

TEST(IsValidStew, GivenEmptyStewInvokedIsValidStewAndIsEmptyExpectedTrueReturnValue) {
    Stew s;
    initStew(s);
    EXPECT_TRUE(isEmpty(s));
    EXPECT_TRUE(isValidStew(s));
}

TEST(IsValidStew, GivenOneNodeInStewInvokedIsValidStewExpectedTrueReturnValue) {
    Stew s;
    initStew(s);
    Node n1;
    
    n1.val = "alpha";
    n1.next = nullptr;
    n1.prev = nullptr;

    s.first = &n1;
    s.last = &n1;
    EXPECT_TRUE(isValidStew(s));
}

TEST(IsValidStew, GivenTwoConnectedNodesInStewInvokedIsValidStewExpectedTrueReturnValue) {
    Stew s;
    initStew(s);
    Node n1;
    Node n2;
    
    n1.val = "alpha";
    n1.next = &n2;
    n1.prev = nullptr;
    
    n2.val = "beta";
    n2.prev = &n1;
    n2.next = nullptr;
    
    s.first = &n1;
    s.last = &n2;
    
    EXPECT_TRUE(isValidStew(s));
}

TEST(IsValidStew, GivenThreeConnectedNodesInStewInvokedIsValidStewExpectedTrueReturnValue) {
    Stew s;
    initStew(s);
    
    Node n1;
    Node n2;
    Node n3;

    n1.val = "alpha";
    n1.next = &n2;
    n1.prev = nullptr;
    
    n2.val = "beta";
    n2.next = &n3;
    n2.prev = &n1;
    
    n3.val = "gamma";
    n3.next = nullptr;
    n3.prev = &n2;
    
    s.first = &n1;
    s.last = &n3;
    
    EXPECT_TRUE(isValidStew(s));
}

TEST(IsValidStew, GivenNullptrFirstAndNotNullLastInvokedIsValidStewExpectedFalseAssertion) {
    Stew s;
    initStew(s);
    
    Node n1;
    n1.val = "alpha";
    n1.next = nullptr;
    n1.prev = nullptr;

    s.last = &n1;

    EXPECT_DEATH(isValidStew(s), "");
}

TEST(IsValidStew, GivenNullptrLastAndNotNullFirstInvokedIsValidStewExpectedFalseAssertion) {
    Stew s;
    initStew(s);
    Node n1;
    
    n1.val = "alpha";
    n1.next = nullptr;
    n1.prev = nullptr;

    s.first = &n1;
    
    EXPECT_DEATH(isValidStew(s), "");
}

TEST(IsValidStew, GivenSelfCycleFirstNodeInvokedIsValidStewExpectedFalseAssertion) {
    Stew s;
    initStew(s);
    Node n1;
    
    n1.val = "alpha";
    n1.next = nullptr;
    n1.prev = nullptr;
    
    s.first = &n1;
    s.last = &n1;

    // create a self-cycle with the node
    n1.next = &n1;
    EXPECT_DEATH(isValidStew(s), "");
}

TEST(IsValidStew, GivenTwoNodesAndNullptrNextForFirstInvokedIsValidStewExpectedFalseAssertion) {
    Stew s;
    initStew(s);
    Node n1;
    Node n2;

    n1.val = "alpha";
    n1.next = nullptr;
    n1.prev = nullptr;
    n2.val = "beta";
    n2.next = nullptr;
    n2.prev = nullptr;
    
    s.first = &n1;
    s.last = &n2;
    s.last->prev = &n1;
    // s.first->next should be &n2, but it isn't
    EXPECT_DEATH(isValidStew(s), "");
}

TEST(IsValidStew, GivenTwoNodesAndNullptrPrevForLastInvokedIsValidStewExpectedFalseAssertion) {
    Stew s;
    initStew(s);
    Node n1;
    Node n2;
    
    n1.val = "alpha";
    n1.next = nullptr;
    n1.prev = nullptr;
    n2.val = "beta";
    n2.next = nullptr;
    n2.prev = nullptr;
    
    s.first = &n1;
    s.last = &n2;
    s.first->next = &n2;
    
    // s.last->prev should be &n1, but it isn't
    EXPECT_DEATH(isValidStew(s), "");
}

/* **** Front Tests ***** */

TEST(Front, GivenEmptyStackThenExpectPeekFrontFails) {
    Stew s1;
    initStew(s1);

    EXPECT_DEATH(peekFront(s1), "");
}

TEST(Front, GivenEmptyStackThenExpectLeaveFrontFails) {
    Stew s1;
    initStew(s1);

    EXPECT_DEATH(leaveFront(s1), "");
}

TEST(Front, GivenOneElementIsAddedToFrontThenExpectItAtBothEnds) {
    Stew s1;
    initStew(s1);

    addFront(s1, "alpha");

    // this is a "whitebox" test because we see inside the structs
    EXPECT_EQ(s1.first, s1.last);
    ASSERT_NE(s1.first, nullptr);
    EXPECT_EQ(nullptr, s1.first->next);
    EXPECT_EQ(nullptr, s1.first->prev);
    EXPECT_EQ("alpha", s1.first->val);

    nuke(s1);
}

TEST(Front, GivenOneElementIsAddedToFrontThenExpectItPeekingBothEnds) {
    Stew s1;
    initStew(s1);

    addFront(s1, "alpha");

    // this is "blackbox" test because we just use the API
    EXPECT_EQ("alpha", peekFront(s1));
    EXPECT_EQ("alpha", peekBack(s1));

    nuke(s1);
}

TEST(Front, GivenAddLeaveThenExpectEmpty) {
    Stew s1;
    initStew(s1);

    addFront(s1, "alpha");
    leaveFront(s1);

    EXPECT_TRUE(isEmpty(s1));

    nuke(s1);
}

TEST(Front, GivenThreeElementsAreAddedToFrontWhenLeaveFrontIsInvokedFirstIsExpectedToBeTheSecondOneThatAdded) {
    Stew s1;
    initStew(s1);

    addFront(s1, "alpha");
    addFront(s1, "beta");
    addFront(s1, "delta");

    leaveFront(s1);

    EXPECT_EQ("beta", peekFront(s1));

    nuke(s1);
}

TEST(Front, GivenThreeElementsAreAddedToFrontWhenLeaveFrontIsInvokedFirstIsExpectedToBeTheFirstOneThatAdded) {
    Stew s1;
    initStew(s1);

    addFront(s1, "alpha");
    addFront(s1, "beta");
    addFront(s1, "delta");

    leaveFront(s1);

    EXPECT_EQ("alpha", peekBack(s1));

    nuke(s1);
}

/* **** Back Tests ***** */

TEST(Back, GivenEmptyStackThenExpectPeekBackFails) {
    Stew s1;
    initStew(s1);

    EXPECT_DEATH(peekBack(s1), "");
}

TEST(Back, GivenEmptyStackThenExpectLeaveBackFails) {
    Stew s1;
    initStew(s1);

    EXPECT_DEATH(leaveBack(s1), "");
}

TEST(Back, GivenOneElementIsAddedToBackThenExpectItAtBothEnds) {
    Stew s1;
    initStew(s1);
    addBack(s1, "alpha");

    // this is a "whitebox" test because we see inside the structs
    EXPECT_EQ(s1.first, s1.last);
    ASSERT_NE(s1.first, nullptr);
    EXPECT_EQ(nullptr, s1.first->next);
    EXPECT_EQ(nullptr, s1.first->prev);
    EXPECT_EQ("alpha", s1.first->val);

    nuke(s1);
}

TEST(Back, GivenOneElementIsAddedToBackThenExpectItPeekingBothEnds) {
    Stew s1;
    initStew(s1);

    addBack(s1, "alpha");

    EXPECT_EQ("alpha", peekFront(s1));
    EXPECT_EQ("alpha", peekBack(s1));

    nuke(s1);
}

TEST(Back, GivenThreeElementsAreAddedToBackWhenLeaveBackIsInvokedLastIsExpectedToBeTheSecondOneThatAdded) {
    Stew s1;
    initStew(s1);

    addBack(s1, "alpha");
    addBack(s1, "beta");
    addBack(s1, "delta");

    leaveBack(s1);

    EXPECT_EQ("beta", peekBack(s1));

    nuke(s1);
}


/* ***** ToString Tests ***** */

TEST(ToString, GivenIllegaDirectionToToStringTheErrorMessageIsExpected) {
    Stew s1;
    initStew(s1);

    string expected = "Error, illegal direction: (k)";
    EXPECT_EQ(expected, toString(s1, 'k'));
}

TEST(ToString, GivenEmptyListWhenToStringIsInvokedAnEmptyStringIsExpected) {
    Stew s1;
    initStew(s1);

    string expected = "[]";
    EXPECT_EQ(expected, toString(s1, 'f'));
}

TEST(ToString, GivenAnElementAddedWithAddFrontWhenToStringIsInvokedTheSameItemExpectedInTheString) {
    Stew s1;
    initStew(s1);

    addFront(s1, "alpha");

    string expected = "[alpha]";
    EXPECT_EQ(expected, toString(s1, 'f'));

    nuke(s1);
}

TEST(ToString, GivenAnElementAddedToFrontAndOneFromBackWhenReverseToStringIsInvokedFirstIsExpectedToBeAfterSecond) {
    Stew s1;
    initStew(s1);

    addBack(s1, "alpha");
    addBack(s1, "delta");

    string expected = "[delta, alpha]";
    EXPECT_EQ(expected, toString(s1, 'r'));

    nuke(s1);
}

TEST(ToString, GivenAnElementAddedToFrontAndOneFromBackWhenToStringIsInvokedSecondIsExpectedToBeAfterFirst) {
    Stew s1;
    initStew(s1);

    addBack(s1, "alpha");
    addBack(s1, "delta");

    string expected = "[alpha, delta]";
    EXPECT_EQ(expected, toString(s1, 'f'));

    nuke(s1);
}

/* ***** Nuke ***** */

// Passing this test is easy from a correctness standpoint.
// The challenge is to get the functionality without memory leaks.
TEST(Nuke, GivenAnElementAddedToFrontWhenNukeIsInvokedAnEmptyListIsExpected) {
    Stew s1;
    initStew(s1);

    addFront(s1, "alpha");
    nuke(s1);

    EXPECT_TRUE(isEmpty(s1));
}
