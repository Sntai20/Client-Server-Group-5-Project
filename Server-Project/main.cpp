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

    // RPCServer* serverObj = new RPCServer(serverIP, port);
    RPCServer* serverObj = new RPCServer();
    serverObj->SetIPAddress(serverIP);
    serverObj->SetPort(port);

#if 0
    std::vector<std::string> tokArray;
    char buffer[128] = { "connect;MIKE;MIKE" };
    serverObj->ParseTokens(buffer, tokArray);
#endif
    // Print when server is working
    statusOk = serverObj->StartServer();
    cout << "\nServer is up!\n" << endl;

    while (statusOk)
    {
        statusOk = serverObj->ListenForClient();
        cout << "\nServer is waiting!\n" << endl;
        statusOk = serverObj->ProcessRPC(); // Launch thread
    }

    delete serverObj;
    return 0;
}