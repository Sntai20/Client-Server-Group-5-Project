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
    // Empty default Constructor is not recommended.
    RPCServer();

    // Destructor breaks the unit test.
    // ~RPCServer();

    // Creates a server on a Port that was passed in, and creates a socket.
    bool StartServer();

    // Accepts a new connection by listening on it's address.
    bool ListenForClient();

    // Examines the buffer and essentially controls connect/disconnect/status.
    bool ProcessRPC();

    /**
     * @brief Extracts tokens from a string vector sent by the client.
     * 
     * @param buffer 
     * @param a 
     */
    // void ParseTokens(char* buffer, vector<string>& a);

    /**
     * @brief The IP addressed assigned to the server.
     * 
     * @param serverIP 
     * @return true 
     * @return false 
     */
    bool SetIPAddress(char* serverIP);

    /**
     * @brief Set the destination port used to listen on.
     * 
     * @param port 
     * @return true 
     * @return false 
     */
    bool SetPort(int port);

    bool GetServerStatus();
    bool SetServerStatus(bool onOrOff);

    int GetSocket();

    int GetRPCCount();

    // Setups up the Bingo Game.
    BingoGame Bingo;

    Socket clientServerConnection;

private:
    int m_rpcCount;
    int m_server_fd;
    int m_socket;
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