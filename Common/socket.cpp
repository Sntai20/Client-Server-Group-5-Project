#include "socket.h"

Socket::Socket(int domain, int type, int protocal)
{
    Socket::optionValue = 1;
    CreateSocket(domain, type, protocal);
}

Socket::~Socket(){}

bool Socket::CreateSocket(int domain, int type, int protocal)
{
    int opt = 1;
    const int BACKLOG = 10;
    
    try
    {
        // Creating socket file descriptor
        Socket::SocketFileDescriptor = socket(domain, type, protocal);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        // std::cerr << "\nSocket failed! open socket error\n" << endl;
    } // end try-catch
    
    try
    {
        // Forcefully attaching socket to the port
        setsockopt(Socket::SocketFileDescriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEADDR, (const void*)&optionValue, sizeof(int));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        // std::cerr << "\nsetsockopt\n" << endl;
    } // end try-catch

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