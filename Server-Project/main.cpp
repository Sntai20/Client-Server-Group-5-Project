/**
 * @file main.cpp
 * @author Group 5
 * @brief Server side C/C++ program to demonstrate Socket programming for Bingo game.
 * @version 0.1
 * @date 2022-02-11
 */  
#include "server.cpp"
/**
 * @brief This is the entry for the server program.
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char* argv[])
{
    char* serverIP = argv[1];
    int port = atoi(argv[2]);
    bool statusOk = true;

    RPCServer* myServer = new RPCServer();
    myServer->SetIPAddress(serverIP);
    myServer->SetPort(port);

    statusOk = myServer->StartServer(); // Print when server is working
    cout << "\nServer is up!" << endl;

    while (statusOk)
    {
        statusOk = myServer->ListenForClient();
        cout << "\nServer is waiting!" << endl;
        statusOk = myServer->ProcessRPC(); // Launch thread
    }

    delete myServer;
    return 0;
}