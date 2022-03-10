#pragma once
/**
 * @file client.h
 * @author Group 5
 * @brief Client side C++ 17 program to demonstrate Socket programming for Bingo game.
 * @version 0.1
 * @date 2022-02-11
 */  

#include <cstdio>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <iterator>
#include <iostream>
#include <cstring>
#include <termio.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#ifdef _WIN32
#include <Winsock2.h>
#include <windows.h>
#include <Ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
#include <iostream>
#include <iterator>
#include <vector>
#include <string.h> // std::strtok uses this library.
#include <algorithm>
#include <thread> // std::this_thread::sleep_for.

using namespace std;

class Client
{
private:
    /* data */
public:
    //Initialize data
    int sock = 0;
    struct sockaddr_in serv_addr;

    //Global variables for supported RPCs calls from client
    const string CONNECT = "connect",
        DISCONNECT = "disconnect",
        SETMAXNUM = "setMaxNum",
        CALC_EXPR = "calculateExpression",
        CALC_STAT = "calculateStats",
        CALC_CONV = "conversion";
    const char* logoffRPC = "disconnect;";
    char buffer[1024] = { 0 };
    char connected;
    char disconnected;
    const int SLEEP_TIME = 10;
    bool bConnect = false;

    string getCredentials();
    void ParseTokens(char* buffer, std::vector<std::string>& a);
    bool ConnectToServer(const char* serverAddress, int port, int& sock);
    void userInterface();
    bool validateInteger(string input);
    // void processSetMaxNum();
    void processCalcExpression();
    void processCalcStats();
    void processConversion();
};
