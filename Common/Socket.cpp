#include "Socket.h"

Socket::Socket()
{
}

Socket::Socket(int domain, int type, int protocal)
{
    Socket::optionValue = 1;
    CreateSocket(domain, type, protocal);
}

Socket::~Socket()
{
}

bool Socket::CreateSocket(int domain, int type, int protocal)
{
    Socket::SocketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (Socket::SocketFileDescriptor < 0)
    {
        std::cerr << "open socket error" << std::endl;
        return 1;
    }


    setsockopt(Socket::SocketFileDescriptor, SOL_SOCKET, SO_REUSEADDR, (const void*)&optionValue, sizeof(int));

    return 0;
}