#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>

constexpr unsigned int SERVER_PORT = 50544;
constexpr unsigned int MAX_BUFFER = 128;

void printMenu() 
{
    std::cout << "\n=========Menu of RPCs with instructions on how to play=========\n";
    std::cout << "The following RPCs must be called prior to setting a board:\n";
    std::cout << "setMaxNum: sets the max number the server will call (must be greater than 25)\n";
    std::cout << "setTime: sets the time interval the server will wait between new numbers (must be less than 10)\n\n";
    std::cout << "To set up a board, the following RPC must be called:\n";
    std::cout << "setBoard: sets the bingo board to a comma separated list of unique numbers.\n"
                 "Input array must be at least 25 numbers long. Game will start after a valid setup.\n\n";
    std::cout << "During the bingo game, the following RPC can be called to mark the board:\n";
    std::cout << "markBoard: marks off the board if the number displayed from the server matches"
                 " a number on the board.\n";
    std::cout << "During the bingo game, the user may call the following RPC to check if there is a bingo:\n";
    std::cout << "checkBingo: checks if a horizontal, vertical or diagonal bingo is on the board."
                 " Ends the game if a valid bingo is detected.\n";


}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Error! usage: ./client localhost" << std::endl;
	return 6;
    }

    std::cout<<"\t\tWelcome to group 5's bingo simulator!";

    std::cout<<"\n\n\t\tEnter IP address to connect to or enter [c] to connect to localhost: \n";

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
    {
        std::cerr << "socket error" << std::endl;
        return 1;
    }

    struct hostent* server = gethostbyname(argv[1]);
    if (server == nullptr) 
    {
        std::cerr << "gethostbyname, no such host" << std::endl;
        return 2;
    }

    struct sockaddr_in serv_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
          (char *)&serv_addr.sin_addr.s_addr, 
          server->h_length);
    serv_addr.sin_port = htons(SERVER_PORT);
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "connect error: the server does not look running" << std::endl;
        return 3;
    }

    std::string readBuffer (MAX_BUFFER, 0);
    

    char buf[100];
    printMenu();
    while (true)
    {
        // Read the responses sent from the server.
        if (read(sockfd, &readBuffer[0], MAX_BUFFER-1) < 0)
        {
            std::cerr << "read from socket failed" << std::endl;
            return 5;
        }
        std::cout << readBuffer << std::endl;

        strcpy(buf,"");
        std::cout<<"\nEnter message to send -> \t";
        // Unused char* fgets
        char* UserInput = fgets(buf,sizeof(buf),stdin);
        if (sizeof(UserInput) < 3 )
        {
            std::cout << "Please enter a valid option." << std::endl;
        }
        // if disconnect is entered, disconnect the client.
        if (strncmp(buf, "disconnect", 10) == 0 ) 
        {
            break;
        }
        if (write(sockfd, buf, strlen(buf)) < 0) 
        {
            std::cerr << "write to socket" << std::endl;
            return 4;
        } 
        else if (write(sockfd, buf, strlen(buf)) == 0) 
        {
            std::cout << "\nServer has terminated connection!" << std::endl;
            close(sockfd);
            break;
        }
    } // End of While loop.

    close(sockfd);
    return 0;
}
