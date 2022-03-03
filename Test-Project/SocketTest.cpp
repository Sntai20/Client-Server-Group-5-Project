#include "../Common/socket.h"
#include "gtest/gtest.h"

// Start of SocketTest
namespace
{
    // To use a test fixture, derive a class from testing::Test.
    class SocketTest : public testing::Test
    {
        protected:  // You should make the members protected s.t. they can be accessed from sub-classes.

        // Declares the variables your tests want to use.
		Socket mySocket_;
    };

    // When you have a test fixture, you define a test using TEST_F instead of TEST.
    // Tests the default optionValue.
    TEST_F(SocketTest, optionValue) 
    {
        int expectedResult = 1;
        EXPECT_EQ(mySocket_.optionValue, expectedResult);
    }
} // End of SocketTest