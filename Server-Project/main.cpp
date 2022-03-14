#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include "../BingoGame/bingogame.h"
#include <arpa/inet.h>
#include <vector>

constexpr unsigned int SERVER_PORT = 50544;
constexpr unsigned int MAX_BUFFER = 128;
constexpr unsigned int MSG_REPLY_LENGTH = 18;

bool relationalOperation(std::string s1, std::string s2)
{
    if (s1 != s2)
    {
        std::cout << s1 << " is not equal to " << s2 << std::endl;
        if (s1 > s2){
            std::cout << s1 << " is greater than " << s2 << std::endl;
            return false;
        }
        else
            std::cout << s2 << " is greater than " << s1 << std::endl;
        return false;
    }
    else
        std::cout << s1 << " is equal to " << s2 << std::endl;
        return true;
}

char* processParameter(char* buffer) 
{
    char* token;
    printf("input: %s\n", buffer);
    char *start = buffer;
    char *end = buffer;
    while(*buffer) {
        if(*buffer == '(')
            start = buffer;
        else if(*buffer == ')')
            end = buffer;
        if(start < end && *start) {
            *end = 0;
            token = start + 1;
            start = buffer = end;
            break;
        }
        buffer++;
    }
    return token;
}

char* setMaxNum() // call setMaxNum function
{
    char* result = (char*)"message";
    return result;
}

char* setTime() // call setTime function
{
    char* result = (char*)"message";
    return result;
}

char* setBoard() // call setBoard function
{
    char* result = (char*)"message";
    return result;
}

int main(int argc, char *argv[])
{
    // client bingo board
    BingoGame bingoBoard = BingoGame();
    
    int sockfd =  socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
    {
        std::cerr << "open socket error" << std::endl;
        return 1;
    }

    int optval = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval , sizeof(int));

    struct sockaddr_in serv_addr, cli_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;  
    serv_addr.sin_addr.s_addr = INADDR_ANY;  
    serv_addr.sin_port = htons(SERVER_PORT);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "bind error" << std::endl;
        return 2;
    }

    listen(sockfd, 5);
    socklen_t clilen = sizeof(cli_addr);
    int incomingSock = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (incomingSock < 0)
    {
        std::cerr << "accept error" << std::endl;
        return 3;
    }

    std::cout << "server: got connection from = " 
                << inet_ntoa(cli_addr.sin_addr)
                << " and port = " << ntohs(cli_addr.sin_port) << std::endl;

     while (true)
     {
        std::string buffer (MAX_BUFFER, 0);
        char sendData[100]; // buffer to hold our sent data
        char* result;
        std::string rest{buffer};
        std::string s1(rest.data());

        ssize_t response = write(incomingSock, "You are connected!", MSG_REPLY_LENGTH);
        if (response < 0)
        {
            std::cout << "Response is less than zero," << std::endl;
        }

        if (read(incomingSock, &buffer[0], MAX_BUFFER-1) < 0)
        {
            std::cerr << "read from socket error" << std::endl;
            return 4;
        }
        std::cout << "Got the message:" << buffer << std::endl;

        // Enumerate through the tokens. The first token is always the specific RPC
        std::vector<std::string> data = { "connect", "disconnect", "setBoard", "markBoard", "setTime", "setMaxNum" };

        for (std::vector<std::string>::iterator t=data.begin(); t != data.end(); ++t) 
        {
            std::cout << *t << std::endl;
            bool isTheSame = false;
            isTheSame = relationalOperation(s1, *t);
            if (isTheSame) 
            { 
                if (relationalOperation(s1,"disconnect")) // disconnect this user
                {
                    std::cout << "\nReceived disconnect RPC" << std::endl;
                    close(incomingSock);
                }
                std::cout << "\nReceived " << *t << " RPC" << std::endl;
                strcpy(sendData,"*t");
                
                if(relationalOperation(s1, "setMaxNum")){
                    result = setMaxNum();
                }  
                if(relationalOperation(s1, "setTime")){
                    result = setTime();
                } 
                if(relationalOperation(s1, "setBoard")){
                    result = setBoard();
                }     

                // Copy the bingo game result to the sendData buffer to be sent to the client.
                strcpy(sendData, result);          
                
            }   // End of string compare.          
            // else if (!isTheSame) 
            // {
            //     strcpy(sendData,(char*)"Invalid RPC. \n");
            // }
            // Send data to client.
            ssize_t response = write(incomingSock, sendData, MSG_REPLY_LENGTH);
            if (response < 0)
            {
                std::cout << "Response is less than zero," << std::endl;
            }
            strcpy(sendData,(char*)""); // clear out the sendData buffer.
        }  // End of For loop.       
     } // End of While loop. 

     close(incomingSock);
     close(sockfd);
     return 0; 
}
