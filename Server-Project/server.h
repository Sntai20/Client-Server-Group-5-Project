/**
 * @file server.h
 * @author Group 5
 * @brief Server side C/C++ program to demonstrate Socket programming for Bingo game.
 * @version 0.1
 * @date 2022-02-11
 */  
#include <cstdio>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <vector>
#include <iterator>
#include <iostream>
#include "../BingoGame/binggame.h"

using namespace std;

/**
 * @brief This RPCServer class contains all the methods to use the server, 
 * including the RPCs.
 * 
 * @param serverIP The IP addressed assigned to the server.
 * @param port The destination port used to listen on.
 * @return An instance of an RPCServer.
 */
class RPCServer
{
public:
    // Constructor
    RPCServer(const char* serverIP, int port);

    // Destructor
    ~RPCServer();

    // Creates a server on a Port that was passed in, and creates a socket.
    bool StartServer();

    // Accepts a new connection by listening on it's address.
    bool ListenForClient();

    // Examines the buffer and essentially controls connect/disconnect/status.
    bool ProcessRPC();

    // Extracts tokens from a string vector sent by the client.
    void ParseTokens(char* buffer, vector<string>& a);

    // Setups up the Bingo Game.
    BingoGame Bingo;

private:
    int m_rpcCount;
    int m_server_fd;
    int m_socket;
    char* m_serverIP;
    int m_port;
    struct sockaddr_in m_address;

    // First one in this function should be a connect, and it
    // will continue try to process RPC's until a Disconnect happens
    bool Connect(std::vector<std::string>& arrayTokens);
    bool StatusRPC();
    bool Disconnect();
};