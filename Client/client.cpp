/*
* PROGRAM: client.cpp
* PURPOSE: Client side C/C++ program to demonstrate Socket programming for Bingo game.
*/
#include <cstdio>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <iterator>
#include <iostream>

/**
void ParseTokens(char* buffer, std::vector<std::string>& a)
{
    char* token;
    char* rest = (char*)buffer;

    while ((token = strtok_r(rest, ";", &rest)))
    {
        //printf("%s\n", token);
        a.push_back(token);
    }
}
*/

// ConnectToServer will connect to the Server based on command line.
bool ConnectToServer(const char* serverAddress, int port, int& sock)
{
    struct sockaddr_in serv_addr {};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\nSocket creation error, please try again. \n");

        return false;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary form.
    if (inet_pton(AF_INET, serverAddress, &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address or Server address not supported, please try again. \n");

        return false;
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed. Please make sure that server is connected.\n");

        return false;
    }

    return true;
}

int main(int argc, char* argv[])
{
    int sock = 0;
    
    const char* connectRPC = "connect;MIKE;MIKE;";
    //const char* statusRPC = "status;";
    const char* logoffRPC = "disconnect;";
    char buffer[1024] = { 0 };
    const char* serverAddress = argv[1];
    const int port = atoi(argv[2]);

    bool bConnect = ConnectToServer(serverAddress, port, sock);

    if (bConnect)
    {
        strcpy(buffer, connectRPC);
        int nlen = strlen(buffer);
        buffer[nlen] = 0;   // Put the null terminator

        send(sock, buffer, strlen(buffer) + 1, 0);
        read(sock, buffer, 1024);

        read(sock, buffer, 1024);
        printf("%s\n", buffer);

        printf("What is your message for the server? ");
        char message[80];
        std::cin.getline(message, sizeof message);
        send(sock, message, strlen(message) + 1, 0);
    }
    else
    {
        printf("\nExit without calling RPC.\n");
    }

    // Sleep 1 to 10 seconds randomly
    int seconds = 1 + (rand() % static_cast<int>(10));
    printf("\nSleeping...\n");
    sleep(seconds);

    // Disconnect Message
    if (bConnect)
    {
        strcpy(buffer, logoffRPC);
        int nlen = strlen(buffer);
        buffer[nlen] = 0;   // Put the null terminator
        send(sock, buffer, strlen(buffer) + 1, 0);
        read(sock, buffer, 1024);

        printf("\nDisconnected.\n");
    }
    else
    {
        printf("\nExit without calling RPC.\n");
    }

    // Terminate connection.
    close(sock);

    return 0;
}