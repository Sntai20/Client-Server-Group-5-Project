#include "socket.h"

Socket::Socket(int domain, int type, int protocal)
{
    Socket::optionValue = 1;
    CreateSocket(domain, type, protocal);
}

Socket::Socket(){
    Socket::optionValue = 1;
}

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
        std::cerr << e.what() << endl;
        cout << "\nSocket failed! open socket error" << endl;
    } // end try-catch
    
    try
    {
        // Forcefully attaching socket to the port
        setsockopt(Socket::SocketFileDescriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEADDR, (const void*)&optionValue, sizeof(int));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << endl;
        cout << "\nsetsockopt" << endl;
    } // end try-catch

    return 0;
}