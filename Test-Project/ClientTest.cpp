#include "../Client-Project/client.h"
#include "gtest/gtest.h"

// Start of ClientTest
namespace
{
    // To use a test fixture, derive a class from testing::Test.
    class ClientTest : public testing::Test
    {
        protected:  // You should make the members protected s.t. they can be accessed from sub-classes.

        // Declares the variables your tests want to use.
		Client myClient_;
    };

    // When you have a test fixture, you define a test using TEST_F instead of TEST.
    // Tests the default sock.
    TEST_F(ClientTest, Sock) 
    {
        int expectedResult = 0;
        EXPECT_EQ(myClient_.sock, expectedResult);
    }
} // End of ClientTest