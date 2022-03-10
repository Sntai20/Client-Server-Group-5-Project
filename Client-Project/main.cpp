/**
 * @file main.cpp
 * @author Group 5
 * @brief Client side C++ 17 program to demonstrate Socket programming for Bingo game.
 * @version 0.1
 * @date 2022-02-11
 */  

#include "client.h"

using namespace std;

//Initialize data
int sock = 0;
struct sockaddr_in serv_addr;

int main(int argc, char const* argv[])
{
    cout << "*   Welcome Bingo Game Client   *" << endl;
    Client* myClient_ = new Client();

    //Check if user entered correct # of Command Line args for IP and Port
    if (argc < 3)
    {
        //If insufficient number of args, print error and exit program.
        cout << "\nMissing IP Address or Port number.\n";
        cout << "Exiting Client Application...\n";
        return -1;
    }

    const char *serverAddress = argv[1];
    const int port = atoi(argv[2]);

    myClient_->bConnect = myClient_->ConnectToServer(serverAddress, port, sock);

    //If we fail to connect to server, exit the program
    if(!myClient_->bConnect){
        cout << "Fail to connect to server, exiting program.." << endl;
        return -1;
    }

    string connectRPC;

    //Start plugging in interface
    //testing if client connect to server
    //keep asking for user input, successfully connected.
    do
    {
        //Reset buffers
        memset(myClient_->buffer, 0 , 1024);
        connectRPC = myClient_->CONNECT + ";";

        //Get credentials from user
        connectRPC = connectRPC + myClient_->getCredentials() + ";";

        //Copy the created the RPC string to the buffer
        strcpy(myClient_->buffer, &connectRPC[0]);

        //Add a null terminator
        int nlen = strlen(myClient_->buffer);
        myClient_->buffer[nlen] = 0;

        //Send the created RPC buffer to server
        send(sock, myClient_->buffer, strlen(myClient_->buffer) + 1, 0);

        //Read from server
        read(sock, myClient_->buffer, 1024);
        myClient_->connected = myClient_->buffer[0];

        //Check if successfully connected
        if (myClient_->connected == '0')
        {
            cout << "\nLogin successful!" << endl;
        }
        else
        {
            cout << "\nInvalid login!" << endl;
        }
    } while (myClient_->connected != '0');

    //Implement user interface
    myClient_->userInterface();

    //Do a Disconnect message
    cout << "Disconnecting from Server" << endl;

    //Reset buffers
    memset(myClient_->buffer, 0 , 1024);

    //Create the buffer to be sent via RPC
    strcpy(myClient_->buffer, myClient_->logoffRPC);
    int nlen = strlen(myClient_->buffer);
    myClient_->buffer[nlen] = 0;   // Put the null terminator

    //Send buffer
    send(sock, myClient_->buffer, strlen(myClient_->buffer) + 1, 0);

    //Get RPC response from server
    read(sock, myClient_->buffer, 1024);
    myClient_->disconnected = myClient_->buffer[0];

    //check if buffer equal to disconnect
    if (myClient_->disconnected == '0')
    {
        cout << "Disconnected successfully" << endl;
    }
    else {
        cout << "Failed to disconnect successfully" << endl;
    }

    //Terminate connection
    close(sock);

    return 0;
}