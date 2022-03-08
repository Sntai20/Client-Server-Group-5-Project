#include "socket.h"

Socket::Socket(int domain, int type, int protocal)
{
    Socket::optionValue = 1;
    CreateSocket(domain, type, protocal);
}

// Socket::Socket(sockaddr_in m_address){
//     this.m_sin_family = m_address.sin_family;
//     this.m
// }

Socket::Socket(){
    Socket::optionValue = 1;
}

bool Socket::CreateSocket(int domain, int type, int protocal)
{
    int opt = 1;
    int valread = 0;
    char buffer[1024] = { 0 };
    const int BACKLOG = 10;
    int addrlen = sizeof(this->m_address);
    this->m_address.sin_family = AF_INET;
    this->m_address.sin_addr.s_addr = INADDR_ANY;
    this->m_address.sin_port = htons(m_port);
    
    
    try
    {
        // Creating socket file descriptor
        this->SocketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
        cout << "SocketFileDescriptor" << endl;
        // Forcefully attaching socket to the port
        setsockopt(this->SocketFileDescriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEADDR, (const void*)&opt, sizeof(int));
        // Forcefully attaching socket to the port 8080
        bind(this->SocketFileDescriptor, (struct sockaddr*)&this->m_address, sizeof(this->m_address));
        (this->incomingSock = accept(this->SocketFileDescriptor, (struct sockaddr*)&this->m_address, (socklen_t*)&addrlen));
        cout << "accept connection" << endl;
        // Should be blocked when a new RPC has not called us yet
        if ((valread = read(this->incomingSock, buffer, sizeof(buffer))) <= 0)
        {
            // TODO: printf("\nErrno is %d\n", errno);
            cout << "broken" << endl;
            // break;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << endl;
        cout << "\nSocket failed! open socket error" << endl;
    } // end try-catch
    
    // try
    // {
        
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << endl;
    //     cout << "\nsetsockopt" << endl;
    // } // end try-catch

    return 0;
}