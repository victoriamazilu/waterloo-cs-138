#include "gtest/gtest.h"
#include "a4p1.h"

using namespace std;

/* ************************************************************** */
/* Tests for Assignment 4 Part 1                                  */
/* ************************************************************** */
// By default this file contains exact copies of all the Marmoset
// public tests in a4p1c.

// Currently these tests achieve 90% coverage on the staff solution.
// To pass a4p1t you will need to augment them to achieve at lest
// 95% coverage on our solution (though, as usual, 100% coverage is
// possible). Note that the Queue functions in the staff solution 
// were moved to a separate file, so you don't need to worry about
// covering them with your tests. Just focus on testing the PQ
// functions.

// Because these tests are for Marmoset, each test can only call the
// function it is specifically meant to run. This makes them large
// and messy. The tests you write don't need to do this. Don't waste
// your time building and destroying linked lists manually. If you
// want to test PQ_first, PQ_leave, PQ_size, etc. use your PQ_enter
// and PQ_nuke functions to create and destroy your testing PQs.

TEST(isEmptyPub, expectEmptyPQIsEmpty) {
    PQ pq;
    PQ_init(pq);
    EXPECT_TRUE(PQ_isEmpty(pq));
}

TEST(isEmptyPub, expectNonEmptyPQIsNotEmpty) {
    // Make the PQ
    Queue priority1;
    priority1.first = priority1.last = new Qnode{"test", nullptr};
    PQ pq = new PQnode{1, priority1, nullptr};

    // Test PQ_isEmpty
    EXPECT_FALSE(PQ_isEmpty(pq));

    // Cleanup
    delete priority1.first;
    delete pq;
}

TEST(enterPub, enterThreeElementsExpectCorrectContents) {
    // Make the PQ
    PQ pq;
    PQ_init(pq);
    PQ_enter(pq, "a", 2);
    PQ_enter(pq, "b", 1);
    PQ_enter(pq, "c", 4);

    // Check the first PQnode
    ASSERT_NE(pq, nullptr);
    EXPECT_EQ(pq->priority, 1);
    EXPECT_EQ(pq->q.first, pq->q.last);
    ASSERT_NE(pq->q.first, nullptr);
    EXPECT_EQ(pq->q.first->val, "b");
    EXPECT_EQ(pq->q.first->next, nullptr);
    ASSERT_NE(pq->next, nullptr);

    // Check the second PQnode
    PQ pq2 = pq->next;
    EXPECT_EQ(pq2->priority, 2);
    EXPECT_EQ(pq2->q.first, pq2->q.last);
    ASSERT_NE(pq2->q.first, nullptr);
    EXPECT_EQ(pq2->q.first->val, "a");
    EXPECT_EQ(pq2->q.first->next, nullptr);
    ASSERT_NE(pq2->next, nullptr);

    // Check the third PQnode
    PQ pq3 = pq2->next;
    EXPECT_EQ(pq3->priority, 4);
    EXPECT_EQ(pq3->q.first, pq3->q.last);
    ASSERT_NE(pq3->q.first, nullptr);
    EXPECT_EQ(pq3->q.first->val, "c");
    EXPECT_EQ(pq3->q.first->next, nullptr);
    EXPECT_EQ(pq3->next, nullptr);

    // delete the PQ manually
    delete pq3->q.first;
    delete pq3;
    delete pq2->q.first;
    delete pq2;
    delete pq->q.first;
    delete pq;
}

TEST(firstPub, givenEmptyPQExpectFirstDies) {
    PQ pq;
    PQ_init(pq);
    EXPECT_DEATH(PQ_first(pq), "Error, priority queue is empty.");
}

TEST(firstPub, givenTheeElementPQExpectFirstGivesCorrectOutput) {
    // Create the two Queues for the PQ
    Queue priority1;
    priority1.first = new Qnode{"alpha", new Qnode{"beta", nullptr}};
    priority1.last = priority1.first->next;
    Queue priority2;
    priority2.first = priority2.last = new Qnode{"delta", nullptr};

    // Create the PQ
    PQ pq = new PQnode{1, priority1, new PQnode{2, priority2, nullptr}};

    // Test PQ_first
    EXPECT_EQ(PQ_first(pq), "alpha");

    // Clean up
    delete pq->next;
    delete pq;
    delete priority1.first;
    delete priority1.last;
    delete priority2.first;
}

TEST(leavePub, givenEmptyPQExpectLeaveDies) {
    PQ pq;
    PQ_init(pq);
    EXPECT_DEATH(PQ_leave(pq), "Error, priority queue is empty.");
}

TEST(leavePub, givenTheeElementPQExpectLeaveRemovesFirst) {
    // Create the two Queues for the PQ
    Queue priority1;
    priority1.first = new Qnode{"alpha", new Qnode{"beta", nullptr}};
    priority1.last = priority1.first->next;
    Queue priority2;
    priority2.first = priority2.last = new Qnode{"delta", nullptr};

    // Create the PQ
    PQ pq = new PQnode{1, priority1, new PQnode{2, priority2, nullptr}};

    // Test PQ_leave
    PQ_leave(pq);

    // Clean up
    delete pq->next;
    delete pq;
    delete priority1.last;
    delete priority2.first;
}

TEST(sizePub, givenEmptyPQExpectSizeIsZero) {
    PQ pq;
    PQ_init(pq);
    EXPECT_EQ(PQ_size(pq), 0);
}

TEST(sizePub, givenTheeElementPQExpectSizeIsThree) {
    // Create the two Queues for the PQ
    Queue priority1;
    priority1.first = new Qnode{"alpha", new Qnode{"beta", nullptr}};
    priority1.last = priority1.first->next;
    Queue priority2;
    priority2.first = priority2.last = new Qnode{"delta", nullptr};

    // Create the PQ
    PQ pq = new PQnode{1, priority1, new PQnode{2, priority2, nullptr}};

    // Test PQ_size
    EXPECT_EQ(PQ_size(pq), 3);

    // Clean up
    delete pq->next;
    delete pq;
    delete priority1.first;
    delete priority1.last;
    delete priority2.first;
}

TEST(sizeByPriorityPub, givenEmptyPQExpectSizeByPriorityIsZero) {
    PQ pq;
    PQ_init(pq);
    EXPECT_EQ(PQ_sizeByPriority(pq, 1), 0);
}

TEST(sizeByPriorityPub, givenTheeElementPQExpectSizeByPriorityIsTwo) {
    // Create the two Queues for the PQ
    Queue priority1;
    priority1.first = new Qnode{"alpha", new Qnode{"beta", nullptr}};
    priority1.last = priority1.first->next;
    Queue priority2;
    priority2.first = priority2.last = new Qnode{"delta", nullptr};

    // Create the PQ
    PQ pq = new PQnode{1, priority1, new PQnode{2, priority2, nullptr}};

    // Test PQ_sizeByPriority
    EXPECT_EQ(PQ_sizeByPriority(pq, 1), 2);

    // Clean up
    delete pq->next;
    delete pq;
    delete priority1.first;
    delete priority1.last;
    delete priority2.first;
}

TEST(numPrioritiesPub, givenEmptyPQExpectZeroPriorities) {
    PQ pq;
    PQ_init(pq);
    EXPECT_EQ(PQ_numPriorities(pq), 0);
}

TEST(nukePub, givenTheeElementPQExpectNukeCleansUp) {
    // Create the two Queues for the PQ
    Queue priority1;
    priority1.first = new Qnode{"alpha", new Qnode{"beta", nullptr}};
    priority1.last = priority1.first->next;
    Queue priority2;
    priority2.first = priority2.last = new Qnode{"delta", nullptr};

    // Create the PQ
    PQ pq = new PQnode{1, priority1, new PQnode{2, priority2, nullptr}};

    // Test PQ_nuke
    PQ_nuke(pq);
    EXPECT_EQ(pq, nullptr);
}



/* ************************************************************** */
/* MORE TESTS HERE                                                */
/* ************************************************************** */
TEST(PQTest, EnterSamePriorityElements) {
    PQ pq;
    PQ_init(pq);
    PQ_enter(pq, "element1", 5);
    PQ_enter(pq, "element2", 5);
    PQ_enter(pq, "element3", 5);

    ASSERT_NE(pq, nullptr);
    ASSERT_NE(pq->q.first, nullptr);
    ASSERT_NE(pq->q.first->next, nullptr);
    EXPECT_EQ(pq->q.first->val, "element1");
    EXPECT_EQ(pq->q.first->next->val, "element2");
    EXPECT_EQ(pq->q.last->val, "element3");
    EXPECT_EQ(pq->next, nullptr);

    PQ_nuke(pq);
} 

TEST(PQTest, LeaveUntilEmptyThenAddMore) {
    PQ pq;
    PQ_init(pq);
    PQ_enter(pq, "element1", 1);
    PQ_enter(pq, "element2", 1);
    PQ_leave(pq);
    PQ_leave(pq);
    EXPECT_TRUE(PQ_isEmpty(pq));

    PQ_enter(pq, "element3", 2);
    EXPECT_FALSE(PQ_isEmpty(pq));
    EXPECT_EQ(PQ_first(pq), "element3");

    PQ_nuke(pq);
}

TEST(PQTest, SizeAfterMultipleOperations) {
    PQ pq;
    PQ_init(pq);
    PQ_enter(pq, "element1", 1);
    PQ_enter(pq, "element2", 2);
    PQ_leave(pq); 
    PQ_enter(pq, "element3", 2);

    EXPECT_EQ(PQ_size(pq), 2);

    PQ_nuke(pq);
}

TEST(PQTest, NumPrioritiesAfterAddingAndRemoving) {
    PQ pq;
    PQ_init(pq);
    PQ_enter(pq, "element1", 1);
    PQ_enter(pq, "element2", 2);
    PQ_enter(pq, "element3", 3);
    EXPECT_EQ(PQ_numPriorities(pq), 3);

    PQ_leave(pq); 
    EXPECT_EQ(PQ_numPriorities(pq), 2);

    PQ_nuke(pq);
}

