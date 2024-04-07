#include "a5p1.h"
#include "gtest/gtest.h"

using namespace std;

/* ************************************************************** */
/* Tests for Assignment 5 Part 1                                  */
/* ************************************************************** */
// By default this file contains exact copies of all the Marmoset
// public tests in a5p1c.

// Currently these tests achieve 78% coverage on the staff solution.
// To pass a5p1t you will need to augment them to achieve 100%
// coverage.

TEST(DogPub, ExpectDogToSpeakItsName) {
	Dog bolt{"Bolt"};
	EXPECT_EQ(bolt.speak(), "    Dog Bolt says \"woof\".");
}

TEST(SheepPub, ExpectSheepToSpeakItsName) {
	Sheep shaun{"Shaun"};
	EXPECT_EQ(shaun.speak(), "    Sheep Shaun says \"baaa\".");
}

TEST(FlockPub, FlockWithNoSheep) {
    Flock spot{"Spot"};
    string expected_output = "The flock of 0 sheep speaks!\n"
                             "    Dog Spot says \"woof\".\n";
    EXPECT_EQ(spot.soundOff(), expected_output);
}

TEST(FlockAddSheep, AddSingleSheepToEmptyFlock) {
    Flock flock{"Lassie"};
    flock.addSheep("Dolly"); // Adding a single sheep to the flock
    flock.addSheep("Dolly"); 
    flock.addSheep("Dolly"); 
    string expected_output = "The flock of 3 sheep speaks!\n"
                             "    Dog Lassie says \"woof\".\n"
                             "    Sheep Dolly says \"baaa\".\n"
                             "    Sheep Dolly says \"baaa\".\n"
                             "    Sheep Dolly says \"baaa\".\n";
    EXPECT_EQ(flock.soundOff(), expected_output);
}

