#include "CommunicatorInterface.h"

CommunicatorInterface::CommunicatorInterface(PCSTR serverIP, PCSTR serverPORT)
{
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
        {
            printf("WSAStartup failed with error: %d\n", iResult);
            delete this;
            return;
        }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = PF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(serverIP, serverPORT, &hints, &result);
    if (iResult != 0)
        {
            printf("getaddrinfo failed with error: %d\n", iResult);
            WSACleanup();
            delete this;
            return;
        }

    Connect();
}
CommunicatorInterface::~CommunicatorInterface()
{
    std::cout << "Shutting down connection.." << std::endl;
    system("pause");
}
void CommunicatorInterface::Connect()
{
    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
        {

            // Create a SOCKET for connecting to server
            ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
                                   ptr->ai_protocol);
            if (ConnectSocket == INVALID_SOCKET)
                {
                    printf("socket failed with error: %ld\n", WSAGetLastError());
                    WSACleanup();
                    delete this;
                    return;
                }

            // Connect to server.
            iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
            if (iResult == SOCKET_ERROR)
                {
                    closesocket(ConnectSocket);
                    ConnectSocket = INVALID_SOCKET;
                    continue;
                }
            break;
        }
    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET)
        {
            printf("Unable to connect to server!\n");
            WSACleanup();
            delete this;
            return;
        }
}
void CommunicatorInterface::Send(char * buffer)
{
    // Send an initial buffer
    iResult = send(ConnectSocket, buffer, (int)strlen(buffer), 0);
    if (iResult == SOCKET_ERROR)
        {
            printf("send failed with error: %d\n", WSAGetLastError());
            closesocket(ConnectSocket);
            WSACleanup();
            system("pause");
            return;
        }
    printf("Bytes Sent: %ld\n", iResult);
}
char * CommunicatorInterface::Receive()
{
    iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
    if (iResult > 0)
        printf("Bytes received: %d\n", iResult);
    else if (iResult == 0)
        printf("Connection closed\n");
    else
        printf("recv failed with error: %d\n", WSAGetLastError());
    return recvbuf;
}
void CommunicatorInterface::Shutdown()
{
    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();
    delete this;
}