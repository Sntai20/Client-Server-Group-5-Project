/**
 * @file main.cpp
 * @author Group 5
 * @brief Client side C++ 17 program to demonstrate Socket programming for Bingo game.
 * @version 0.1
 * @date 2022-02-11
 */  
#include "client.cpp"
#include <iostream>
// #include <fstream> 

/**
 * @brief This is the entry for the client program.
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char* argv[])
{
    Client myClient;
    
    const char* connectRPC = "connect;MIKE;MIK;";
    // TODO: const char* statusRPC = "status;";
    const char* logoffRPC = "disconnect;";
    char destinationBuffer[1024] = { 0 };
    const char* serverAddress = argv[1];

    /* stoi Function for converting a string to an integer. 
     * https://www.techiedelight.com/convert-string-to-int-cpp/
     */
    const int port = std::stoi(argv[2]);
    bool bConnect = myClient.ConnectToServer(serverAddress, port);

    if (bConnect)
    {
        
        // TODO: strcpy(buffer, connectRPC);
        int sizeOfDestination = sizeof(destinationBuffer);
        std::memcpy(destinationBuffer, connectRPC, sizeOfDestination);
        // TODO:int nlen = strlen(buffer);
        
        // TODO:
        destinationBuffer[sizeOfDestination] = 0;   // Put the null terminator

        // TODO:send(sock, buffer, strlen(buffer) + 1, 0);
        send(bConnect, destinationBuffer, sizeOfDestination + 1, 0);
        // TODO:
        // read(bConnect, destinationBuffer, 1024);

        // TODO:read(sock, buffer, 1024);
        cout << destinationBuffer << endl;

        cout << "What is your message for the server? " << endl;
        char message[80];
        std::cin.getline(message, sizeof message);
        // TODO:
        send(bConnect, message, strlen(message) + 1, 0);
        std::cout << "connected" << endl;
    }
    else
    {
        cout << "\nExit without calling RPC." << endl;
    }

    /**
     * @brief sleep_for 1 to 10 seconds randomly
     * https://www.cplusplus.com/reference/thread/this_thread/sleep_for/
     */ 
    int seconds = 1 + (rand() % static_cast<int>(10));
    cout << "\nSleeping..." << endl;
    std::this_thread::sleep_for(std::chrono::seconds(seconds));

    // Disconnect Message
    if (bConnect)
    {
        // TODO:strcpy(buffer, logoffRPC);
        // TODO:int nlen = strlen(buffer);
        // TODO:buffer[nlen] = 0;   // Put the null terminator
        // TODO:send(sock, buffer, strlen(buffer) + 1, 0);
        // TODO: read(sock, buffer, 1024);

        cout << "\nDisconnected." << endl;
    }
    else
    {
        cout << "\nExit without calling RPC.\n" << endl;
    }

    // Terminate connection.
    close(myClient.sock);

    return 0;
}