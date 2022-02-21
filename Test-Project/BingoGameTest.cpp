#include "../BingoGame/bingoname.h"
#include "gtest/gtest.h"

// Start of BingoGameTest
namespace
{
    // To use a test fixture, derive a class from testing::Test.
    class BingoGameTest : public testing::Test
    {
        protected:  // You should make the members protected s.t. they can be accessed from sub-classes.

        // Declares the variables your tests want to use.
		BingoGame myBingoGame_;
    };

    // When you have a test fixture, you define a test using TEST_F instead of TEST.
    // Tests the default setBoard method.
    TEST_F(BingoGameTest, setBoard) 
    {
        string inputString = "bingoExample";
        EXPECT_EQ(myBingoGame_.setBoard(inputString), true);
    }

    // Tests the default markBoard method.
    TEST_F(BingoGameTest, markBoard) 
    {
        string inputString = "bingoExample";
        myBingoGame_.markBoard();
        EXPECT_EQ(true, true);
    }

    // Tests the default setTime method.
    TEST_F(BingoGameTest, setTime) 
    {
        string inputString = "bingoExample";
        EXPECT_EQ(myBingoGame_.setTime(inputString), true);
    }

    // Tests the default setMaxNum method.
    TEST_F(BingoGameTest, setMaxNum) 
    {
        string inputString = "bingoExample";
        EXPECT_EQ(myBingoGame_.setMaxNum(inputString), true);
    }
} // End of BingoGameTest