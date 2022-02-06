#include "client.h"

unsigned int SERVER_PORT = 50544;
unsigned int MAX_BUFFER = 128;

Client::Client(){}

Client::~Client(){}

bool Client::Start()
{
    clientServerConnection.CreateSocket(AF_INET, SOCK_STREAM, 0);
    
    // TODO: Replace hardcoded hostname value.
    struct hostent* server = gethostbyname("ansantan");
    if (server == nullptr)
    {
        std::cerr << "gethostbyname, no such host" << std::endl;
        return 2;
    }

    struct sockaddr_in serv_addr;
    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char*)server->h_addr,
        (char*)&serv_addr.sin_addr.s_addr,
        server->h_length);

    serv_addr.sin_port = htons(SERVER_PORT);
    if (connect(clientServerConnection.SocketFileDescriptor, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "connect error" << std::endl;
        return 3;
    }

    std::string readBuffer(MAX_BUFFER, 0);
    if (read(clientServerConnection.SocketFileDescriptor, &readBuffer[0], MAX_BUFFER - 1) < 0)
    {
        std::cerr << "read from socket failed" << std::endl;
        return 5;
    }
    std::cout << readBuffer << std::endl;

    // This loop keeps the connection open.
    while (true)
    {
        std::string writeBuffer(MAX_BUFFER, 0);
        std::cout << "What message for the server? : ";
        getline(std::cin, writeBuffer);
        if (write(clientServerConnection.SocketFileDescriptor, writeBuffer.c_str(), strlen(writeBuffer.c_str())) < 0)
        {
            std::cerr << "write to socket" << std::endl;
            return 4;
        }
    }

	return false;
}

bool Client::Stop()
{
	return close(clientServerConnection.SocketFileDescriptor);
}