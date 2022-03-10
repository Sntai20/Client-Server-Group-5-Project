#include "../BingoGame/bingogame.h"
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
    // Tests the default setTime method.
    TEST_F(BingoGameTest, setTime)
    {
        string inputString = "5";
        bool result = myBingoGame_.setTime(inputString);
        EXPECT_TRUE(result);
    }

    // Tests the default setMaxNum method.
    TEST_F(BingoGameTest, setMaxNum)
    {
        string inputString = "50";
        bool result = myBingoGame_.setMaxNum(inputString);
        EXPECT_TRUE(result);
    }

    // Tests the default checkUnique method used in setBoard.
    TEST_F(BingoGameTest, checkUnique) 
    {
        myBingoGame_.setMaxNum("25");
        string inputString = "1,2,3,4,5,8,7,9,19,14,12,13,15,11,35,32,23,24,25,26,28,39,37,46,50";
        bool result = myBingoGame_.checkUnique(inputString);
        EXPECT_TRUE(result);
    }
    
    // Tests the default setBoard method while setting the max number to 50.
    TEST_F(BingoGameTest, setBoard) 
    {
        myBingoGame_.setMaxNum("25");
        string inputString = "1,2,3,4,5,8,7,9,19,14,12,13,15,11,35,32,23,24,25,26,28,39,37,46,50";
        bool result = myBingoGame_.setBoard(inputString);
        EXPECT_TRUE(result);
    }

    // Tests the default markBoard method.
    TEST_F(BingoGameTest, markBoard) 
    {
        bool result = myBingoGame_.markBoard();
        EXPECT_FALSE(result);
    }

    // Tests the default checkBingo method.
    TEST_F(BingoGameTest, checkBingo)
    {
        bool result = myBingoGame_.checkBingo();
        EXPECT_FALSE(result);
    }
	
} // End of BingoGameTest