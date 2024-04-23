#include <string>
#include "gtest/gtest.h"
#include "a6p3.h"

using namespace std;

// By default this file contains copies of the Marmoset tests in a6p3c.
// Currently they get 70% coverage on our solution. To pass the a6p3t coverage
// test you will need to augment them so that they get full coverage (100%
// lines executed).

// Note: The provided powerset and addChar functions were moved to another file
// in the solution on Marmoset, so you don't have to worry about covering them
// in a6p3t. Just focus on the two scabbleValue overloads and bestScrabbleWord

TEST(scrabbleValueCharPub, testAFewChars) {
    EXPECT_EQ(scrabbleValue('a'), 1);
    EXPECT_EQ(scrabbleValue('b'), 3);
    EXPECT_EQ(scrabbleValue('c'), 3);
}

TEST(scrabbleValueCharPub, testNonLetterCharacterGivesCorrectDeath) {
    EXPECT_DEATH(scrabbleValue('1'), "Error: Received non-alphabetical character \'1\'");
}

TEST(scrabbleValueStringPub, testEmptyStringHasValueZero) {
    EXPECT_EQ(scrabbleValue(""), 0);
}

TEST(scrabbleValueStringPub, testNonLetterCharacterGivesCorrectDeath) {
    EXPECT_DEATH(scrabbleValue("2"), "Error: Received non-alphabetical character \'2\'");
}

TEST(bestScrabbleWordPub, bestWordThatCanBeMadeFromNothingIsNothing) {
    EXPECT_EQ(bestScrabbleWord(""), "");
}

TEST(bestScrabbleWordPub, testNonLetterCharacterGivesCorrectDeath) {
    EXPECT_DEATH(bestScrabbleWord("3"), "Error: Received non-alphabetical character \'3\'");
}

TEST(bestScrabbleWordPub, testBigNumberGivesCorrectDeath) {
    EXPECT_DEATH(bestScrabbleWord("313"), "Error: Received non-alphabetical character \'3\'");
}

TEST(scrabbleValueStringPub, CaseInsensitiveScoring) {
    EXPECT_EQ(scrabbleValue("AbC"), 1 + 3 + 3);  // A=1, b=3, C=3
}

TEST(scrabbleValueStringPub, ScoresAllLetters) {
    int expectedScore = 10*1 + 2*2 + 4*3 + 5*4 + 1*5 + 2*8 + 2*10;
    EXPECT_EQ(scrabbleValue("abcdefghijklmnopqrstuvwxyz"), expectedScore);
}

TEST(BestScrabbleWordTest, HandlesDifferentRepeatingLetters) {
    EXPECT_EQ(bestScrabbleWord("aardvarkkk"), "aardvark"); 
}

TEST(BestScrabbleWordTest, CaseInsensitiveInputHandling) {
    EXPECT_EQ(bestScrabbleWord("MiXeD"), "MiXeD");
}
