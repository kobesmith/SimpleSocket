#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")  
#define BUF_SIZE 100

int main(int argc, char* argv[])
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET sock = socket(PF_INET, SOCK_DGRAM, 0);

    sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));  
    servAddr.sin_family = PF_INET;
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servAddr.sin_port = htons(1234);

    sockaddr fromAddr;
    int addrLen = sizeof(fromAddr);
    while(1)
	{
        char buffer[BUF_SIZE] = {0};
        printf("Input a string: ");
        gets_s(buffer);
        sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr*)&servAddr, sizeof(servAddr));
        int strLen = recvfrom(sock, buffer, BUF_SIZE, 0, &fromAddr, &addrLen);
        buffer[strLen] = 0;
        printf("Message form server: %s\n", buffer);
    }

    closesocket(sock);

    WSACleanup();
    return 0;
}