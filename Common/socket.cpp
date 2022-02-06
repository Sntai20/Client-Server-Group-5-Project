#include "socket.h"
#include <stdio.h>

Socket::Socket(int domain, int type, int protocal)
{
    Socket::optionValue = 1;
    CreateSocket(domain, type, protocal);
}

Socket::~Socket(){}

bool Socket::CreateSocket(int domain, int type, int protocal)
{
    Socket::SocketFileDescriptor = socket(domain, type, protocal);
    if (Socket::SocketFileDescriptor < 0)
    {
        std::cerr << "open socket error" << std::endl;
        return 1;
    }

    setsockopt(Socket::SocketFileDescriptor, SOL_SOCKET, SO_REUSEADDR, (const void*)&optionValue, sizeof(int));

    return 0;
}

// Returns the current counter value, and increments it.
int Socket::Increment() 
{
    return counter_++;
}

// Returns the current counter value, and decrements it.
// counter can not be less than 0, return 0 in this case
int Socket::Decrement() 
{
    if (counter_ == 0) 
    {
        return counter_;
    }
    else 
    {
        return counter_--;
    }
}