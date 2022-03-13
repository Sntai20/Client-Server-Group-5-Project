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

bool relationalOperation(std::string s1, std::string s2)
{
 
    if (s1 != s2)
    {
        std::cout << s1 << " is not equal to " << s2 << std::endl;
        if (s1 > s2)
            std::cout << s1 << " is greater than " << s2 << std::endl;
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

int main(int argc, char *argv[])
{
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
     write(incomingSock, "You are connected!", MSG_REPLY_LENGTH);

     std::string buffer (MAX_BUFFER, 0);
     if (read(incomingSock, &buffer[0], MAX_BUFFER-1) < 0)
     {
          std::cerr << "read from socket error" << std::endl;
          return 4;
     }
     std::cout << "Got the message:" << buffer << std::endl;
     // buffer to hold our sent data
    char sendData[100];
     
    std::string rest{buffer};
    //  if(strstr(buffer,"disconnect"))
    std::string s1(rest.data());
    std::string s2("disconnect");
    
    if (relationalOperation(s1, s2))
    { // disconnect this user
        
        printf("\nReceived disconnect RPC\n");

        strcpy(sendData,"Disconnected!\n");
        // Sleep(10);
        // send(current_client,sendData,sizeof(sendData),0);
        write(incomingSock, sendData, MSG_REPLY_LENGTH);

        // close the socket associated with this client and end this thread
        // closesocket(current_client);
        // ExitThread(0);
    }

     close(incomingSock);
     close(sockfd);
     return 0; 
}
