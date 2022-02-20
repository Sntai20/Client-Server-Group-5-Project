/**
 * @file client.cpp
 * @author Group 5
 * @brief Client side C/C++ program to demonstrate Socket programming for Bingo game.
 * @version 0.1
 * @date 2022-02-11
 */  
// #include <cstdio>
// #include <sys/socket.h>
// #include <arpa/inet.h>
// #include <unistd.h>
// #include <cstring>
// #include <vector>
// #include <iterator>
// #include <iostream>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief This method is used to parse the tokens sent by the client.
 * 
 * @param buffer 
 * @param a 
 */
// void ParseTokens(char* buffer, vector<string>& a)
// {
//     char* token;
//     char* rest = (char*)buffer;

//     while ((token = strtok_r(rest, ";", &rest)))
//     {
//         //printf("%s\n", token);
//         a.push_back(token);
//     }
// }

/**
 * @brief ConnectToServer will connect to the Server based on command line.
 * 
 * @param serverAddress 
 * @param port 
 * @param sock 
 * @return true 
 * @return false 
 */
bool ConnectToServer()
// bool ConnectToServer(const char* serverAddress, int port, int& sock)
{
    // struct sockaddr_in serv_addr;
    // try
    // {
    //     (sock = socket(AF_INET, SOCK_STREAM, 0));
    // }
    // catch(const exception& e)
    // {
    //     cout << "\nSocket creation error, please try again. \n" << endl;
    //     std::cerr << e.what() << '\n';
    //     return false;
    // }

    // serv_addr.sin_family = AF_INET;
    // serv_addr.sin_port = htons(port);

    // try
    // {
    //     // Convert IPv4 and IPv6 addresses from text to binary form.
    //     inet_pton(AF_INET, serverAddress, &serv_addr.sin_addr);
    // }
    // catch(const std::exception& e)
    // {
    //     cout << "\nInvalid address or Server address not supported, please try again. \n" << endl;
    //     std::cerr << e.what() << '\n';
    //     return false;
    // }

    // try
    // {
    //     connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    // }
    // catch(const std::exception& e)
    // {
    //     cout << "\nConnection Failed. Please make sure that server is connected.\n" << endl;
    //     std::cerr << e.what() << '\n';
    //     return false;
    // }

    return true;
}