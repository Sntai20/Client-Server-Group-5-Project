#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include "../Common/socket.cpp"

using namespace std;

class Client : Socket
{
public:
	Client();
	~Client();
	Socket clientServerConnection;
	bool Start();
	bool Stop();

private:

};