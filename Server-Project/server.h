#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include "../Common/socket.cpp"

class Server : Socket
{
public:
	Server();
	~Server();
	Socket clientServerConnection;
	bool Start();
	bool Stop();

private:

};