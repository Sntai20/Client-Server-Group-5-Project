//
// Created by Antonio Santana on 1/22/22.
//
// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <cstdio>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
//#define PORT 8080
#include <iostream>

int main()
{
    printf("started");
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
//    char *hello = "Hello from server";
    const void *hello = "Hello from server";
    std::string hello2 = "Hello from server";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    printf("Forcefully attaching socket to the port 8080");
    printf("setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));");

//    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
//    {
//        perror("setsockopt");
//        exit(EXIT_FAILURE);
//    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
//    address.sin_port = htons( PORT );
//    printf("We are using Port: {0}", address.sin_port);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    valread = read( new_socket , buffer, 1024);
    printf("%s\n",buffer );
//    send(new_socket , hello ,  strlen(hello) , 0 );
    size_t messageSize = hello2.length();
    send(new_socket , hello ,  messageSize , 0 );
    printf("Hello message sent\n");

    std::cout << "Server Hello, World!" << std::endl;
    return 0;
}
