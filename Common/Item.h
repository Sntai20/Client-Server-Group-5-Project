#include <iostream>

// Data contract between producer and consumer.
struct Item
{
	int age;
	std::string firstName;
	std::string lastName;
	std::string password;
	std::string message;
	std::string token;
};