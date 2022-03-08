/**
 * @file main.cpp
 * @author Group 5
 * @brief Server side C++ program to demonstrate Socket programming for Bingo game.
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

    Server* myServer = new Server(serverIP, port);
    // myServer->SetIPAddress(serverIP);
    // myServer->SetPort(port);

    statusOk = myServer->StartServer(); // Print when server is working
    cout << "\nServer is up!" << endl;

    while (statusOk)
    {
        cout << "server is okay" << endl;
        /**
         * @brief ListenForClient is used to call the MultiThreadedProcessRPC. 
         * MultiThreadedProcessRPC starts the threads and to process the client 
         * connections.
         */
        statusOk = myServer->ListenForClient(); 
        cout << "Server is online listening for client connections!" << endl; 
        statusOk = myServer->ProcessRPC();
        /* TODO: Add multi threading to the listener. We probably want 
        * to queue the incoming connections and have a thread to process
        * an individual connection. The client and thread would be a 
        * one to one relationship. Each client connection would be 
        * processed by one thread on the server.
        * 
        * Process the incoming RPC.
        */
        // while (currentServerStatus == connected)
        // {
        //     this->MultiThreadedProcessRPC();
        // }
    }

    delete myServer;
    return 0;
}