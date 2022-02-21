#pragma once
// #include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>

using namespace std;

class Socket
{
public:

    // Creates a counter that starts at 0.
    Socket() : counter_(0) {}

    // Returns an intialized socket.
    Socket(int domain, int type, int protocal);

    // Destructor. Breaks the unit test.
    // ~Socket();

    // Returns the file handle value as an int.
    int SocketFileDescriptor;

    // Returns 0 if the socket was created, otherwise the return value is 1.
    bool CreateSocket(int domain, int type, int protocal);
    int optionValue = 0;

    // Returns the current counter value, and increments it.
    int Increment();

    // Returns the current counter value, and decrements it.
    int Decrement();

private:
    int counter_;
};