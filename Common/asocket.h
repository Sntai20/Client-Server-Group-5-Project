#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>


class Socket
{
public:
    Socket();
    Socket(int domain, int type, int protocal);
    ~Socket();
    int SocketFileDescriptor;
    bool CreateSocket(int domain, int type, int protocal);
    int optionValue;

private:

};