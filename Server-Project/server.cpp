/**
 * @file server.cpp
 * @author Group 5
 * @brief Server side C++ 17 program to demonstrate Socket programming for Bingo game.
 * @version 0.1
 * @date 2022-02-11
 */  
#include "server.h"
#include "LocalContext.h"

/**
 * @brief Struct to maintain the global context for threads.
 * 
 */
typedef struct _GlobalContext 
{
    int g_rpcCount;
} GlobalContext;

GlobalContext globalObj; // We need to protect this, as we don't want bad data

/**
 * @brief Construct a new RPCServer::RPCServer object
 * 
 */
RPCServer::RPCServer()
{
    m_rpcCount = 0;
};

/**
 * @brief This method starts the server with an intialized socket.
 * 
 * @return true 
 * @return false 
 */
bool RPCServer::StartServer()
{
    m_address.sin_family = AF_INET;
    m_address.sin_addr.s_addr = INADDR_ANY;
    m_address.sin_port = htons(m_port);
    try
    {
        clientServerConnection.CreateSocket(m_address.sin_family, SOCK_STREAM, 0);
        // Forcefully attaching socket to the port 8080
        bind(clientServerConnection.SocketFileDescriptor, (struct sockaddr*)&m_address, sizeof(m_address));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << endl;
        cout << "\nBind failed." << endl;
    } // end try-catch

    this->SetServerStatus(true); // Set the server status to on.
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
    // TODO: Add multi threading to the listener.
    const int BACKLOG = 10;
    int addrlen = sizeof(m_address);

    try
    {
        listen(m_server_fd, BACKLOG);
        (incomingSock = accept(m_server_fd, (struct sockaddr*)&m_address, (socklen_t*)&addrlen));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << endl;
    } // end try-catch

    this->ProcessRPC();
    return true;
}

/**
 * @brief This method is used to process RPCs from a client.
 * 
 * @return true 
 * @return false 
 */
bool RPCServer::ProcessRPC()
{
    cout << "Process all the RPCs" << endl;
    // Enumerate through the tokens. The first token is always the specific RPC
    // vector<string> data = { "connect", "disconnect", "status", "setBoard", "markBoard", "setTime", "setMaxNum" };
    // for (vector<string>::iterator t=data.begin(); t!=data.end(); ++t) 
    // {
    //     cout<<*t<<endl;
    // }

    // Create a map of three (strings, int) pairs
    std::map<std::string, int> rpcTable 
    { 
        {"connect", 10}, 
        {"disconnect", 15}, 
        {"status", 20}, 
        {"markBoard", 25}, 
        {"setTime", 30}, 
        {"setMaxNum", 35} 
    };
    
    // Enumerate through the tokens. The first token is always the specific RPC
    for (auto const& [key, val] : rpcTable)
    {
        std::cout << key << ':' << val << std::endl;
    }

    return true;
}
// bool RPCServer::ProcessRPC()
// {
//     const char* rpcs[] = { "connect", "disconnect", "status" };
//     char buffer[1024] = { 0 };
//     std::vector<std::string> arrayTokens;
//     int valread = 0;
//     bool bConnected = false;
//     bool bStatusOk = true;
//     const int RPCTOKEN = 0;
//     bool bContinue = true;

//     while ((bContinue) && (bStatusOk))
//     {
//         // Should be blocked when a new RPC has not called us yet
//         if ((valread = read(this->incomingSock, buffer, sizeof(buffer))) <= 0)
//         {
//             // TODO: printf("\nErrno is %d\n", errno);
//             break;
//         }
//         //printf("%s\n", buffer);

//         arrayTokens.clear();
//         // this->ParseTokens(buffer, arrayTokens);

//         /* // TODO:
//         // Enumerate through the tokens. The first token is always the
//         // specific RPC
//         for (vector<string>::iterator t = arrayTokens.begin(); t !=
//          arrayTokens.end(); ++t)
//         {
//             printf("\nDebugging our tokens.\n");
//             printf("\nToken = %s\n", t);
//         }
//         */

//         // string statements are not supported with a switch, so using if/else logic to dispatch
//         string aString = arrayTokens[RPCTOKEN];

//         if ((bConnected == false) && (aString == "connect"))
//         {
//             // Connect RPC
//             bStatusOk = Connect(arrayTokens);
//             if (bStatusOk == true)
//                 bConnected = true;
//             cout << "\nClient is connected!" << endl;

//             // Let the client know about connection
//             const char* message = "\nYou are now connected to the server!\n";
//             send(this->incomingSock, message, strlen(message) + 1, 0);

//             // Call hard-coded RPC functions with set values until they are implemented
//             // After client is connected, Set the board
//             // while (!Bingo.setBoard("1,2,3,4,5,8,7,9,19,14,12,13,15,11,35,32,23,24,25,26,28,39,37,46,50")) 
//             // {
//             //     // Board not succesfully set: prompt user for new input (mandatory valid input required)
//             // }
            
//             // // Board is marked if the current number in the server is valid
//             // Bingo.markBoard();

//             // while (!Bingo.setMaxNum("5")) 
//             // {
//             //     // max num not succesfully set: prompt user for new input (mandatory valid input required)
//             // }

//             // while (!Bingo.setTime("5")) 
//             // {
//             //     // Time not succesfully set: prompt user for new input (mandatory valid input required)
//             // }

//             // Get the client response
//             // TODO: Replace with c++ version. read(this->m_socket, buffer, sizeof(buffer));
//             cout << "A message from connected client: " << buffer << endl;
//         }
//         else if ((bConnected == true) && (aString == "disconnect"))
//         {
//             // Terminating the endless loop
//             bStatusOk = Disconnect();
//             cout << "\nClient is disconnected now!" << endl;
//             // We are going to leave this loop, as we are done
//             bContinue = false;
//         }
//         else if ((bConnected == true) && (aString == "status"))
//         {
//             // Status RPC
//             bStatusOk = StatusRPC();
//         }
//         else
//         {
//             // Not in our list, perhaps, print out what was sent
//             // TODO: Log or throw an exception.
//         }
//     }

//     return true;
// }


/**
 * @brief This method is used to parse the tokens sent by the client.
 * 
 * @param buffer 
 * @param a 
 */
// void RPCServer::ParseTokens(char* buffer, std::vector<std::string>& arrayToken)
// {
//     char* token;
//     char* rest = (char*)buffer;

//     while ((token = strtok_r(rest, ";", &rest)))
//     {
//         cout << token << endl;
//         arrayToken.push_back(token);
//     }
// }

/**
 * @brief This method is used to parse the tokens sent by the client.
 * Extracts tokens from a string vector sent by the client.
 * @param buffer 
 * @param a 
 */
// void RPCServer::ParseTokens(char* buffer, vector<string>& a)
// {
//     char* token;
//     string rest{buffer};
//     char const * const delimiter{";"};
//     char * psz_token{strtok(rest.data(), delimiter)};
//     while(nullptr != psz_token)
//     {
//         cout << psz_token << endl;
//         psz_token = strtok(nullptr, delimiter);
//         cout << token << endl;
//         a.push_back(token);
//     }
// }

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
* @brief The IP addressed assigned to the server.
* 
* @param serverIP 
* @return true 
* @return false 
*/
bool RPCServer::SetIPAddress(char* serverIP)
{
    m_serverIP = serverIP;
    return true;
}

/**
 * @brief Set the destination port used to listen on.
 * 
 * @param port 
 * @return true 
 * @return false 
 */
bool RPCServer::SetPort(int port)
{
    m_port = port;
    return true;
}

bool RPCServer::GetServerStatus(){
    return this->m_ServerStatus;
}

bool RPCServer::SetServerStatus(bool onOrOff){
    this->m_ServerStatus = onOrOff;
    return true;
}

int RPCServer::GetSocket()
{
    return this->incomingSock;
}

int RPCServer::GetRPCCount()
{
    return this->m_rpcCount;
    
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
    // TODO: Authentication
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
    send(this->incomingSock, szBuffer, strlen(szBuffer) + 1, 0);

    // TODO: Replace with c++ version. read(this->m_socket, szBuffer, sizeof(szBuffer) <= 0);

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
    send(this->incomingSock, szBuffer, strlen(szBuffer) + 1, 0);

    return true;
}

/**
 * @brief A normal C function that is executed as a thread
 * when its name is specified in pthread_create()
 * 
 * @param vargp 
 * @return void* 
 */
void* myThreadFun(void* vargp)
{

    sleep(1);

    int socket = *(int *) vargp;
    cout << "Printing GeeksQuiz from Thread \n" << endl;
    // TODO: RPCServer *rpcImplObj = new RPCServer(socket);
    // TODO: rpcImplObj->ProcessRPC();   // This will go until client disconnects;
    cout << "Done with Thread" << endl;

    return NULL;
}