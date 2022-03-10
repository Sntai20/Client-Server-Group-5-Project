// Client code for windows version
#ifdef _WIN32
#include <Ws2tcpip.h>
#include <Winsock2.h>
#include <windows.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
#include <stdio.h>
#include <iostream>
#include <signal.h>

//DECLARATIONS
//error trapping signals
#define SIGINT 2
#define SIGKILL 9
#define SIGQUIT 3
// SOCKETS
SOCKET sock,client;

void s_handle(int s)
{
    if(sock)
        closesocket(sock);
    if(client)
        closesocket(client);
    WSACleanup();
    Sleep(1000);
    std::cout<<"EXIT SIGNAL :"<<s;
    exit(0);
}


void s_cl(char *a, int x)
{
    std::cout<<a;
    s_handle(x+1000);
}

void printMenu() {

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


int main()
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE|FOREGROUND_INTENSITY);

    //Declarations
    DWORD poll;
    int res,i=1,port=8080;
    char buf[100];
    char msg[100] = "";
    char ip[15];
    WSADATA data;

    signal(SIGINT,s_handle);
    signal(SIGKILL,s_handle);
    signal(SIGQUIT,s_handle);


    std::cout<<"\t\tWelcome to group 5's bingo simulator!";

    std::cout<<"\n\n\t\tEnter IP address to connect to or enter [c] to connect to localhost: \n";

    gets(ip);
    // if the first letter in the buffer is "c", set ip to localhost
    if (strncmp(ip, "c", 1) == 0 ) {
        strcpy(ip, "127.0.0.1");
    }

    sockaddr_in ser;
    sockaddr addr;

    ser.sin_family=AF_INET;
    ser.sin_port=htons(8080);                    //Set the port
    ser.sin_addr.s_addr=inet_addr(ip);      //Set the address we want to connect to

    memcpy(&addr,&ser,sizeof(SOCKADDR_IN));

    res = WSAStartup(MAKEWORD(1,1),&data);      //Start Winsock

    if(res != 0)
        s_cl((char*)"WSAStartup failed",WSAGetLastError());

    sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);       //Create the socket
    if(sock==INVALID_SOCKET )
        s_cl((char*)"Invalid Socket ",WSAGetLastError());
    else if(sock==SOCKET_ERROR)
        s_cl((char*)"Socket Error)",WSAGetLastError());
    else
        std::cout<<"Socket Established!"<<std::endl;



    res=connect(sock,&addr,sizeof(addr));               //Connect to the server
    if(res !=0 )
    {
        s_cl((char*)"Connection to server failed! Please make sure the server is running.",res);
    }
    else
    {
        std::cout<<"\nSuccessfully Connected to Server!";
        memcpy(&ser,&addr,sizeof(SOCKADDR));
    }
    char RecvdData[100] = "";
    strcpy(RecvdData,"");
    int ret;
    char* successfulLogin = (char*)"Successfully logged in!";
    while (strncmp(RecvdData, successfulLogin, strlen(successfulLogin)) != 0) {
        std::cout<<"\nPlease enter your login credentials in the following format: [connect;username;password].\n";
        strcpy(buf,"");
        fgets(buf,sizeof(buf),stdin);
        res = send(sock,buf,sizeof(buf),0);
        ret = recv(sock,RecvdData,sizeof(RecvdData),0);
        if(ret > 0)
        {
            std::cout<<std::endl<<RecvdData;
            if (strncmp(RecvdData, successfulLogin, strlen(successfulLogin)) == 0) {
                break;
            } else{
                strcpy(RecvdData,"");
            }
        }
    }

    printMenu();
    while(true)
    {
        strcpy(buf,"");
        std::cout<<"\nEnter message to send ->\n";
        fgets(buf,sizeof(buf),stdin);


        // if disconnect is entered, disconnect the client.
        if (strncmp(buf, "disconnect", 10) == 0 ) {
            break;
        }

        Sleep(25);
        res = send(sock,buf,sizeof(buf),0);

        if(res==0)
        {
            //0==other side terminated conn
            printf("\nServer has terminated connection!\n");
            Sleep(40);
            closesocket(client);
            client = 0;
            break;
        }
        else if(res==SOCKET_ERROR)
        {
            //-1 == send error
            printf("Socket error\n");
            Sleep(40);
            s_handle(res);
            break;
        }

        // expect extra lines of output from server for setBoard and markBoard RPCs
        ret = recv(sock,RecvdData,sizeof(RecvdData),0);
        if (strncmp(buf, "setBoard", 8) == 0 || strncmp(buf, "markBoard", 9) == 0 ) {
            for (int i = 0; i < 8 ; i++) {
                recv(sock,RecvdData,sizeof(RecvdData),0);
                std::cout<<RecvdData;
                strcpy(RecvdData,"");
            }
        } else if(ret > 0)
        {
            std::cout<<std::endl<<RecvdData;
            strcpy(RecvdData,"");
        }
    }

    closesocket(client);
    WSACleanup();
}
