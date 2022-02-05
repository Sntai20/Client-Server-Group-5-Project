
#include "Server.h"

constexpr unsigned int SERVER_PORT = 50544;
constexpr unsigned int MAX_BUFFER = 128;
constexpr unsigned int MSG_REPLY_LENGTH = 18;

Server::Server() 
{

}

Server::~Server() 
{

}

bool Server::Start() 
{
	
    clientServerConnection.CreateSocket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr, cli_addr;
    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(SERVER_PORT);
    if (bind(clientServerConnection.SocketFileDescriptor, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "bind error" << std::endl;
        return 2;
    }

    listen(clientServerConnection.SocketFileDescriptor, 5);
    socklen_t clilen = sizeof(cli_addr);
    int newsockfd = accept(clientServerConnection.SocketFileDescriptor, (struct sockaddr*)&cli_addr, &clilen);
    if (newsockfd < 0)
    {
        std::cerr << "accept error" << std::endl;
        return 3;
    }

    std::cout << "server: got connection from = "
        << inet_ntoa(cli_addr.sin_addr)
        << " and port = " << ntohs(cli_addr.sin_port)
        << std::endl;

    write(newsockfd, "You are connected!", MSG_REPLY_LENGTH);

    // This loop keeps the connection open.
    while (true)
    {
        std::string buffer(MAX_BUFFER, 0);
        if (read(newsockfd, &buffer[0], MAX_BUFFER - 1) < 0)
        {
            std::cerr << "read from socket error" << std::endl;
            return 4;
        }
        std::cout << "Got the message:" << buffer << std::endl;
    }
}

bool Server::Stop() 
{
    return close(Server::clientServerConnection.SocketFileDescriptor);
}