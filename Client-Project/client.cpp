/**
 * @file client.cpp
 * @author Group 5
 * @brief Client side C++ 17 program to demonstrate Socket programming for Bingo game.
 * @version 0.1
 * @date 2022-02-11
 */  
#include "client.h"

/**
 * @brief This method is used to parse the tokens sent by the client.
 * 
 * @param buffer 
 * @param a 
 */
void Client::ParseTokens(char* buffer, vector<string>& a)
{
    char* token;
    string rest{buffer};
    char const * const delimiter{";"};
    char * psz_token{strtok(rest.data(), delimiter)};
    while(nullptr != psz_token)
    {
        cout << psz_token << endl;
        psz_token = strtok(nullptr, delimiter);
        cout << token << endl;
        a.push_back(token);
    }
}

/**
 * @brief ConnectToServer will connect to the Server based on command line.
 * 
 * @param serverAddress 
 * @param port 
 * @param sock 
 * @return true 
 * @return false 
 */
bool Client::ConnectToServer(const char* serverAddress, int port)
{
    struct sockaddr_in serv_addr;
    try
    {
        (sock = socket(AF_INET, SOCK_STREAM, 0));
    }
    catch(const exception& e)
    {
        cout << "\nSocket creation error, please try again." << endl;
        std::cerr << e.what() << endl;
        return false;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    try
    {
        // Convert IPv4 and IPv6 addresses from text to binary form.
        inet_pton(AF_INET, serverAddress, &serv_addr.sin_addr);
    }
    catch(const std::exception& e)
    {
        cout << "\nInvalid address or Server address not supported, please try again." << endl;
        std::cerr << e.what() << endl;
        return false;
    }

    try
    {
        connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    }
    catch(const std::exception& e)
    {
        cout << "\nConnection Failed. Please make sure that server is connected." << endl;
        std::cerr << e.what() << '\n';
        return false;
    }

    return true;
}