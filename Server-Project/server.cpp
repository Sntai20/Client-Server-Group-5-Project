/**
 * @file server.cpp
 * @author Group 5
 * @brief Server side C/C++ program to demonstrate Socket programming for Bingo game.
 * @version 0.1
 * @date 2022-02-11
 */  
#include "server.h"

/**
 * @brief Construct a new RPCServer::RPCServer object
 * 
 * @param serverIP 
 * @param port 
 */
RPCServer::RPCServer(const char* serverIP, int port)
{
    m_rpcCount = 0;
    m_serverIP = (char*)serverIP;
    m_port = port;
};

/**
 * @brief Destroy the RPCServer::RPCServer object
 */
RPCServer::~RPCServer() {};

/**
 * @brief This method starts the server with an intialized socket.
 * 
 * @return true 
 * @return false 
 */
bool RPCServer::StartServer()
{
    int opt = 1;
    const int BACKLOG = 10;
    
    try
    {
        // Creating socket file descriptor
        (m_server_fd = socket(AF_INET, SOCK_STREAM, 0));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        perror("\nSocket failed!\n");
    } // end try-catch

   try
   {
       // Forcefully attaching socket to the port
       setsockopt(m_server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
   }
   catch(const std::exception& e)
   {
       std::cerr << e.what() << '\n';
       perror("\nsetsockopt\n");
   } // end try-catch

    m_address.sin_family = AF_INET;
    m_address.sin_addr.s_addr = INADDR_ANY;
    m_address.sin_port = htons(m_port);

    try
    {
        // Forcefully attaching socket to the port 8080
        bind(m_server_fd, (struct sockaddr*)&m_address, sizeof(m_address));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        perror("\nBind failed.\n");
    } // end try-catch
    
    try
    {
        listen(m_server_fd, BACKLOG);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        perror("\nListen\n");
    } // end try-catch
    
    return true;
}

/**
 * @brief This method is used to listen for incoming requests.
 * 
 * @return true 
 * @return false 
 */
bool RPCServer::ListenForClient()
{
    int addrlen = sizeof(m_address);

    try
    {
        (m_socket = accept(m_server_fd, (struct sockaddr*)&m_address, (socklen_t*)&addrlen));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        perror("\nAccept\n");
    } // end try-catch
    
    this->ProcessRPC();

    return true;
}

/**
 * @brief This method is used to parse the tokens sent by the client.
 * 
 * @param buffer 
 * @param a 
 */
void RPCServer::ParseTokens(char* buffer, std::vector<std::string>& a)
{
    char* token;
    char* rest = (char*)buffer;

    while ((token = strtok_r(rest, ";", &rest)))
    {
        //printf("%s\n", token);
        a.push_back(token);
    }
}

/**
 * @brief This method is used to process RPCs from a client.
 * 
 * @return true 
 * @return false 
 */
bool RPCServer::ProcessRPC()
{
    const char* rpcs[] = { "connect", "disconnect", "status" };
    char buffer[1024] = { 0 };
    std::vector<std::string> arrayTokens;
    int valread = 0;
    bool bConnected = false;
    bool bStatusOk = true;
    const int RPCTOKEN = 0;
    bool bContinue = true;

    while ((bContinue) && (bStatusOk))
    {
        // Should be blocked when a new RPC has not called us yet
        if ((valread = read(this->m_socket, buffer, sizeof(buffer))) <= 0)
        {
            //printf("\nErrno is %d\n", errno);
            break;
        }
        //printf("%s\n", buffer);

        arrayTokens.clear();
        this->ParseTokens(buffer, arrayTokens);

        /*
        // Enumerate through the tokens. The first token is always the
        // specific RPC
        for (vector<string>::iterator t = arrayTokens.begin(); t !=
         arrayTokens.end(); ++t)
        {
            printf("\nDebugging our tokens.\n");
            printf("\nToken = %s\n", t);
        }
        */

        // string statements are not supported with a switch, so using if/else logic to dispatch
        string aString = arrayTokens[RPCTOKEN];

        if ((bConnected == false) && (aString == "connect"))
        {
            // Connect RPC
            bStatusOk = Connect(arrayTokens);
            if (bStatusOk == true)
                bConnected = true;
            printf("\nClient is connected!\n");

            // Let the client know about connection
            const char* message = "\nYou are now connected to the server!\n";
            send(this->m_socket, message, strlen(message) + 1, 0);

            // Call hard-coded RPC functions with set values until they are implemented
            // After client is connected, Set the board
            while (!Bingo.setBoard("1,2,3,4,5,8,7,9,19,14,12,13,15,11,35,32,23,24,25,26,28,39,37,46,50")) 
            {
                // Board not succesfully set: prompt user for new input (mandatory valid input required)
            }
            
            // Board is marked if the current number in the server is valid
            Bingo.markBoard();

            while (!Bingo.setMaxNum("5")) 
            {
                // max num not succesfully set: prompt user for new input (mandatory valid input required)
            }

            while (!Bingo.setTime("5")) 
            {
                // Time not succesfully set: prompt user for new input (mandatory valid input required)
            }

            // Get the client response
            read(this->m_socket, buffer, sizeof(buffer));
            printf("A message from connected client: %s\n", buffer);
        }
        else if ((bConnected == true) && (aString == "disconnect"))
        {
            // Terminating the endless loop
            bStatusOk = Disconnect();
            printf("\nClient is disconnected now!\n");
            // We are going to leave this loop, as we are done
            bContinue = false;
        }
        else if ((bConnected == true) && (aString == "status"))
        {
            // Status RPC
            bStatusOk = StatusRPC();
        }
        else
        {
            // Not in our list, perhaps, print out what was sent
            // TODO: Log or throw an exception.
        }
    }

    return true;
}

/**
 * @brief This method is used to connect and authenticate 
 * the incomming requests.
 * 
 * @param arrayTokens 
 * @return true 
 * @return false 
 */
bool RPCServer::Connect(std::vector<std::string>& arrayTokens)
{
    const int USERNAMETOKEN = 1;
    const int PASSWORDTOKEN = 2;

    // Strip out tokens 1 and 2 (username, password)
    string userNameString = arrayTokens[USERNAMETOKEN];
    string passwordString = arrayTokens[PASSWORDTOKEN];
    char szBuffer[80];

    // Authentication Logic. MIKE/MIKE is the only valid combination
    if ((userNameString == "MIKE") && (passwordString == "MIKE"))
    {
        strcpy(szBuffer, "1;"); // Connected
    }
    else
    {
        strcpy(szBuffer, "0;"); // Not Connected
    }

    // Send Response back on our socket
    int nlen = strlen(szBuffer);
    szBuffer[nlen] = 0;
    send(this->m_socket, szBuffer, strlen(szBuffer) + 1, 0);

    read(this->m_socket, szBuffer, sizeof(szBuffer) <= 0);

    return true;
}

/**
 * @brief This method provides the RPC status.
 * 
 * @return true 
 * @return false 
 */
bool RPCServer::StatusRPC()
{
    // TODO: Implement.
    return true;
}

/**
 * @brief This method is used to disconnect the connection.
 * 
 * @return true 
 * @return false 
 */
bool RPCServer::Disconnect()
{
    char szBuffer[16];
    strcpy(szBuffer, "disconnect");
    // Send Response back on our socket
    int nlen = strlen(szBuffer);
    szBuffer[nlen] = 0;
    send(this->m_socket, szBuffer, strlen(szBuffer) + 1, 0);

    return true;
}