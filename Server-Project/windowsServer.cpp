// Server code for windows version
#include <stdio.h>
#ifdef _WIN32
#include <Ws2tcpip.h>
#include <Winsock2.h>
#include <windows.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
#include "bingogame.h"

char* processParameter(char* buf) {
    char* token;
    printf("input: %s\n", buf);
    char *start = buf;
    char *end = buf;
    while(*buf) {
        if(*buf == '(')
            start = buf;
        else if(*buf == ')')
            end = buf;
        if(start < end && *start) {
            *end = 0;
            token = start + 1;
            start = buf = end;
            break;
        }
        buf++;
    }
    return token;
}

// our thread for receiving commands
DWORD WINAPI receive_cmds(LPVOID lpParam)
{
    printf("Thread Created!\r\n");

    // set our socket to the socket passed in as a parameter
    SOCKET current_client = (SOCKET)lpParam;

    // buffer to hold our received data
    char buf[100];
    // buffer to hold our sent data
    char sendData[100];
    // for error checking
    int res;
    // boolean to check if a valid user is logged in
    bool authenticated = false;
    // client bingo board
    BingoGame bingoBoard = BingoGame();
    // our recv loop
    while(true)
    {
        res = recv(current_client,buf,sizeof(buf),0); // recv cmds

        Sleep(10);

        if(res == 0)
        {
            MessageBox(0,"error","error",MB_OK);
            closesocket(current_client);
            ExitThread(0);
        }

        if (!authenticated) {
            if(strstr(buf,"connect;USER1;PASSWORD1") ||
               strstr(buf,"connect;USER2;PASSWORD2") ||
               strstr(buf,"connect;USER3;PASSWORD3") ||
               strstr(buf,"connect;USER4;PASSWORD4") ||
               strstr(buf, "c")) // last combination is for quick testing
            { // greet this user
                printf("\nSuccessful login from user!\n");

                strcpy(sendData,"Successfully logged in!\n");
                Sleep(10);
                send(current_client,sendData,sizeof(sendData),0);
                authenticated = true;
            } else {
                strcpy(sendData,"Invalid login credentials. Please try again.\n");
                Sleep(10);
                send(current_client,sendData,sizeof(sendData),0);
            }
        } else {
            if(strstr(buf,"disconnect"))
            { // disconnect this user
                printf("\nReceived disconnect RPC\n");

                strcpy(sendData,"Disconnected!\n");
                Sleep(10);
                send(current_client,sendData,sizeof(sendData),0);

                // close the socket associated with this client and end this thread
                closesocket(current_client);
                ExitThread(0);
            }
            else if(strstr(buf,"setMaxNum"))
            { // call setMaxNum function
                printf("\nReceived setMaxNum RPC\n");
                char* parameter = processParameter(buf);
                bool success = bingoBoard.setMaxNum((string)parameter);
                char message [100];
                if (success) {
                    strcpy(message, (char*)"Successfully set! The max number that the server will call will be ");
                    strcat(message, parameter);
                } else {
                    strcpy(message, (char*)"The max number provided was invalid. Please enter a new number greater than 25.");
                }
                strcpy(sendData, message);
                Sleep(10);
                send(current_client,sendData,sizeof(sendData),0);
            }
            else if(strstr(buf,"setTime"))
            { // call setTime function
                printf("\nReceived setTime RPC\n");
                char* parameter = processParameter(buf);
                bool success = bingoBoard.setTime((string)parameter);
                char message [100];
                if (success) {
                    strcpy(message, (char*)"Successfully set! The delay between each server call will be ");
                    strcat(message, parameter);
                    strcat(message, (char*)" seconds.");
                } else {
                    strcpy(message, (char*)
                            "The delay provided was invalid. Please enter a new number less than or"
                            " equal to 10 seconds.");
                }
                strcpy(sendData, message);
                Sleep(10);
                send(current_client,sendData,sizeof(sendData),0);
            }
            else if(strstr(buf,"setBoard"))
            { // call setBoard function
                printf("\nReceived setBoard RPC\n");
                char* parameter = processParameter(buf);
                bool success = bingoBoard.setBoard((string)parameter);
                char message [100];
                if (success) {
                    strcpy(message, (char*)"Successfully set bingo board!");
                    strcpy(sendData, message);
                    Sleep(10);
                    send(current_client,sendData,sizeof(sendData),0);

                    char bingoLine [100];
                    // print bingo board line by line
                    for (int i = 0; i < 7; i++) {
                        strcpy(sendData, bingoBoard.printDelimiterBoard(bingoLine,i));
                        while (send(current_client,sendData,sizeof(sendData),0) < 0){
                            send(current_client,sendData,sizeof(sendData),0);
                        }
                        strcpy(bingoLine, "");
                        strcpy(sendData, "");
                    }

                } else {
                    strcpy(message, (char*)"Invalid bingo setup provided. Please try again.");
                    strcpy(sendData, message);
                    Sleep(10);
                    send(current_client,sendData,sizeof(sendData),0);
                    for (int i = 0; i < 7; i++) {

                        while (send(current_client,sendData,sizeof(sendData),0) < 0){
                            send(current_client,sendData,sizeof(sendData),0);
                        }
                        strcpy(sendData, "");
                    }
                }
                strcpy(sendData, message);
                Sleep(10);
                send(current_client,sendData,sizeof(sendData),0);

            }

            else if(strstr(buf,"markBoard"))
            { // call markBoard function
                printf("\nReceived markBoard RPC\n");
                char* parameter = processParameter(buf);
                bool success = bingoBoard.markBoard();
                char message [100];
                if (success) {
                    strcpy(message, (char*)"Successfully marked bingo board!");
                    strcpy(sendData, message);
                    Sleep(10);
                    send(current_client,sendData,sizeof(sendData),0);

                    char bingoLine [100];
                    // print bingo board line by line
                    for (int i = 0; i < 7; i++) {
                        strcpy(sendData, bingoBoard.printDelimiterBoard(bingoLine,i));
                        while (send(current_client,sendData,sizeof(sendData),0) < 0){
                            send(current_client,sendData,sizeof(sendData),0);
                        }
                        strcpy(bingoLine, "");
                        strcpy(sendData, "");
                    }

                } else {
                    strcpy(message, (char*)"Number called by the server not found in current bingo board.");
                }
                strcpy(sendData, message);
                Sleep(10);
                send(current_client,sendData,sizeof(sendData),0);

            }
            else if(strstr(buf,"checkBingo"))
            { // call checkBingo function
                printf("\nReceived checkBingo RPC\n");
                bool success = bingoBoard.checkBingo();
                char message [100];
                if (success) {
                    strcpy(message, (char*)"Bingo detected! Game will now end...");
                    //TODO: MAKE GAME END AND OFFER TO PLAY AGAIN OR DISCONNECT CLIENT
                } else {
                    strcpy(message, (char*)"No bingo detected. Please try again later!");
                }
                strcpy(sendData, message);
                Sleep(10);
                send(current_client,sendData,sizeof(sendData),0);
            }
            else
            {
                strcpy(sendData,"Invalid RPC. \n");
                Sleep(10);
                send(current_client,sendData,sizeof(sendData),0);
            }
        }

        // clear buffers
        strcpy(sendData,"");
        strcpy(buf,"");
    }
}

int main()
{
    printf("Starting up multi-threaded TCP server!\r\n");

    // our masterSocket(socket that listens for connections)
    SOCKET sock;

    // for our thread
    DWORD thread;

    WSADATA wsaData;
    sockaddr_in server;

    // start winsock
    int ret = WSAStartup(0x101,&wsaData); // use highest version of winsock avalible

    if(ret != 0)
    {
        return 0;
    }

    // fill in winsock struct ...
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(8080); // listen on telnet port 8080

    // create our socket
    sock=socket(AF_INET,SOCK_STREAM,0);

    if(sock == INVALID_SOCKET)
    {
        return 0;
    }

    // bind our socket to a port(port 8080)
    if( bind(sock,(sockaddr*)&server,sizeof(server)) !=0 )
    {
        return 0;
    }

    // listen for a connection
    if(listen(sock,5) != 0)
    {
        return 0;
    }

    // socket that we snedzrecv data on
    SOCKET client;

    sockaddr_in from;
    int fromlen = sizeof(from);

    // loop forever
    while(true)
    {
        // accept connections
        client = accept(sock,(struct sockaddr*)&from,&fromlen);
        printf("Client connected!\r\n");

        // create our recv_cmds thread and parse client socket as a parameter
        CreateThread(NULL, 0,receive_cmds,(LPVOID)client, 0, &thread);
    }

    // shutdown winsock
    closesocket(sock);
    WSACleanup();

    // exit
    return 0;
}
