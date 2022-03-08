#include "BingoGameTest.cpp"
#include "ClientTest.cpp"
#include "ServerTest.cpp"
#include "gtest/gtest.h"

/**
 * @brief This is the main entry to initialize the Google test framework and run all the tests.
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char** argv) 
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}