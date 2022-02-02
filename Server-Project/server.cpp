#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>

constexpr unsigned int SERVER_PORT = 50544;
constexpr unsigned int MAX_BUFFER = 128;
constexpr unsigned int MSG_REPLY_LENGTH = 18;

class ServerClass
{
public:
    ServerClass();
    ~ServerClass();
    int sockfd;

private:

};

ServerClass::ServerClass()
{
}

ServerClass::~ServerClass()
{
}

int main(int argc, char* argv[])
{
    ServerClass myServer;
    myServer.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (myServer.sockfd < 0)
    {
        std::cerr << "open socket error" << std::endl;
        return 1;
    }

    int optval = 1;
    setsockopt(myServer.sockfd, SOL_SOCKET, SO_REUSEADDR, (const void*)&optval, sizeof(int));

    struct sockaddr_in serv_addr, cli_addr;
    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(SERVER_PORT);
    if (bind(myServer.sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "bind error" << std::endl;
        return 2;
    }

    listen(myServer.sockfd, 5);
    socklen_t clilen = sizeof(cli_addr);
    int newsockfd = accept(myServer.sockfd, (struct sockaddr*)&cli_addr, &clilen);
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

    close(newsockfd);
    close(myServer.sockfd);
    return 0;
}