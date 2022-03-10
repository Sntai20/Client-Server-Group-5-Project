/**
 * @file main.cpp
 * @author Group 5
 * @brief Server side C++ program to demonstrate Socket programming for Bingo game.
 * @version 0.1
 * @date 2022-02-11
 */  
#include "server.cpp"
#include <cstdio>
#include <iostream>
/**
 * @brief This is the entry for the server program.
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */



/**
 * The main() function starts the server applications, waits for client connection, then process RPCs from the client.
 *
 * This is an endless server, thus will not exit unless it hits an error, or terminated from the OS
 *
 * @param argc An int containing the number input arguments
 * @param argv A char array containing the command line arguments. Expecting IP Address, port number
 *              (e.g. 127.0.0.1 8080)
 * @return An int value with the exit status
 */
int main(int argc, char* argv[])
{
    cout << "************************************************" << endl;
    cout << "*   Welcome to the Group 5 Server Application  *" << endl;
    cout << "************************************************" << endl;

    //check if user entered correct # of Command Line args for IP and Port
    if (argc < 3)
    {
        //If insufficient number of args, print error and exit program.
        cout << "\nMissing IP Address or Port number.\n";
        cout << "Exiting Server Application...\n";
        return -1;
    }

    // Extract serverIP and port numbers from command line arguments
    char* serverIP = argv[1];
    int port = atoi(argv[2]);

    //Declare a bool flag to track the status of the system
    bool statusOk = true;

    //Declare a server object variable to handle the server operations
    Server* serverObj = new Server();
    serverObj->SetIPAddress(serverIP);
    serverObj->SetPort(port);

    //Get server Status
    statusOk = serverObj->StartServer();

    //Print Server Status
    if (statusOk)
    {
        cout << "\nServer is now running\n" << endl;
    }
    else
    {
        cout << "\nServer failed to start\n" << endl;
    }

    //While loop listening to client and processing the incoming RPC calls
    while (statusOk)
    {
        //printf("\nWaiting...\n");
        statusOk = serverObj->ListenForClient();

    }

    //delete the serverObj and free up its memory
    delete serverObj;
    serverObj = nullptr;

    //Return success to OS
    return 0;
}