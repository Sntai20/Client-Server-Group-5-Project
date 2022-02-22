#pragma once
/**
 * @file server.h
 * @author Group 5
 * @brief Server side C++ 17 program to demonstrate Socket programming for Bingo game.
 * @version 0.1
 * @date 2022-02-11
 */  
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "../Common/socket.cpp"
#include "../BingoGame/bingoname.h"

using namespace std;

/**
 * @brief This RPCServer class contains all the methods to use the server, 
 * including the RPCs.
 * 
 * @return An instance of an RPCServer.
 */
class RPCServer
{
public:
    RPCServer(); // Empty default Constructor is not recommended.
    // ~RPCServer(); Destructor breaks the unit test.
    bool StartServer(); // Creates a server on a Port that was passed in, and creates a socket.
    bool ListenForClient(); // Accepts a new connection by listening on it's address.
    bool ProcessRPC(); // Examines the buffer and essentially controls connect/disconnect/status.
    // void ParseTokens(char* buffer, vector<string>& a); // Extracts tokens from a string vector sent by the client.
    bool SetIPAddress(char* serverIP);
    bool SetPort(int port);
    bool GetServerStatus();
    bool SetServerStatus(bool onOrOff);
    int GetSocket();
    int GetRPCCount();
    BingoGame Bingo; // Abstracts the Bingo Game.
    Socket clientServerConnection; // Abstracts the socket connection.

private:
    int m_rpcCount;
    int m_server_fd;
    int incomingSock;
    char* m_serverIP;
    int m_port;
    struct sockaddr_in m_address;
    bool m_ServerStatus = false;

    // First one in this function should be a connect, and it
    // will continue try to process RPC's until a Disconnect happens
    bool Connect(std::vector<std::string>& arrayTokens);
    bool StatusRPC();
    bool Disconnect();
};