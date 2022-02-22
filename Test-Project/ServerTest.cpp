// A sample program demonstrating using Google C++ testing framework.

// In this example, we use a more advanced feature of Google Test called
// test fixture.
//
// A test fixture is a place to hold objects and functions shared by
// all tests in a test case.  Using a test fixture avoids duplicating
// the test code necessary to initialize and cleanup those common
// objects for each test.  It is also useful for defining sub-routines
// that your tests need to invoke a lot.
//
// <TechnicalDetails>
//
// The tests share the test fixture in the sense of code sharing, not
// data sharing.  Each test is given its own fresh copy of the
// fixture.  You cannot expect the data modified by one test to be
// passed on to another test, which is a bad idea.
//
// The reason for this design is that tests should be independent and
// repeatable.  In particular, a test should not fail as the result of
// another test's failure.  If one test depends on info produced by
// another test, then the two tests should really be one big test.
//
// The macros for indicating the success/failure of a test
// (EXPECT_TRUE, FAIL, etc) need to know what the current test is
// (when Google Test prints the test result, it tells you which test
// each failure belongs to).  Technically, these macros invoke a
// member function of the Test class.  Therefore, you cannot use them
// in a global function.  That's why you should put test sub-routines
// in a test fixture.
//
// </TechnicalDetails>
#include "../Server-Project/server.h"
#include "../Server-Project/server.cpp"
#include "gtest/gtest.h"


// Start of ServerTest
namespace 
{
    // To use a test fixture, derive a class from testing::Test.
    class ServerTest : public testing::Test 
    {
        protected:  // You should make the members protected s.t. they can be accessed from sub-classes.
        // Declares the variables your tests want to use.
		RPCServer* myServer_ = new RPCServer();
    };

    // When you have a test fixture, you define a test using TEST_F instead of TEST.

    // Tests StartServer().
    TEST_F(ServerTest, StartServer) 
    {
        bool expectedResult;
        expectedResult = myServer_->StartServer();
        EXPECT_EQ(true, expectedResult);
    }

    // Tests GetServerStatus().
    TEST_F(ServerTest, GetServerStatus) 
    {
        bool expectedResult;
        myServer_->StartServer();
        expectedResult = myServer_->GetServerStatus();
        EXPECT_EQ(true, expectedResult);
    }

    // Tests GetRPCCount().
    TEST_F(ServerTest, GetRPCCount) 
    {
        bool expectedResult;
        expectedResult = myServer_->GetRPCCount();
        EXPECT_EQ(false, expectedResult);
    }

    // Tests the ListenForClient() function.
    TEST_F(ServerTest, ListenForClient) 
    {
        bool expectedResult;
        expectedResult = myServer_->ListenForClient();
        EXPECT_EQ(true, expectedResult);
        
        // Terminate connection.
        close(myServer_->GetSocket());
    }

    // Tests the ProcessRPC function.
    TEST_F(ServerTest, ProcessRPC) 
    {
        bool expectedResult;
        expectedResult = myServer_->ProcessRPC();
		EXPECT_EQ(true, expectedResult);
	}

    // Tests my understanding of gtests.
    // TEST_F(ServerTest, ParseTokens) 
    // {
    //     std::vector<std::string> arrayTokens;
    //     // const char* connectRPC = "connect;MIKE;MIKE;";
    //     // char buffer[1024] = { 0 };
    //     char buffer{"connect;MIKE;MIKE;"};
    //     // strcpy_s(buffer, 1024, connectRPC);

    //     myServer_.ParseTokens(buffer, arrayTokens);
        
	// 	EXPECT_EQ("MIKE", arrayTokens.end);
	// }
}  // End of ServerTest