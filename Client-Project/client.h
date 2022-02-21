/**
 * @file client.h
 * @author Group 5
 * @brief Client side C++ 17 program to demonstrate Socket programming for Bingo game.
 * @version 0.1
 * @date 2022-02-11
 */  
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <iterator>
#include <vector>
#include <string.h> // std::strtok uses this library.
#include <algorithm>
#include <thread> // std::this_thread::sleep_for.
#include "../Common/socket.h"

using namespace std;

class Client
{
private:
    /* data */
public:
    // Client(/* args */);
    // ~Client();
    int sock = 0;
    void ParseTokens(char* buffer, vector<string>& a);
    bool ConnectToServer(const char* serverAddress, int port);
};