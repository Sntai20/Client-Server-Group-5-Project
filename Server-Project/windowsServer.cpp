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
            char *token = start + 1;
            printf("token: %s\n", token);

            start = buf = end;
            return token;
        }
        buf++;
    }

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
               strstr(buf,"connect;USER4;PASSWORD4"))
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
            if(strstr(buf,"hello"))
            { // greet this user
                printf("\nreceived hello cmd");

                strcpy(sendData,"hello from server\n");
                Sleep(10);
                send(current_client,sendData,sizeof(sendData),0);
            }
            else if(strstr(buf,"disconnect"))
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
            { // disconnect this user
                printf("\nReceived setMaxNum RPC\n");
                char* parameter = processParameter(buf);
                bingoBoard.setMaxNum((string)parameter);

                strcpy(sendData,parameter);
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
