#pragma once

#include "Core.h"

class CommunicatorInterface
{
    std::string buffer;
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL;
    struct addrinfo *ptr = NULL;
    struct addrinfo  hints;
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;
public:
    CommunicatorInterface(PCSTR serverIP=DEFAULT_IP, PCSTR serverPORT=DEFAULT_PORT);
    ~CommunicatorInterface();
    void Connect();
    void Send(char * buffer);
    char * Receive();
    void Shutdown();
};

