#include <stdio.h>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll
#define BUF_SIZE 100

int main(int argc, char* argv[])
{
    WSADATA wsaData;
    WSAStartup( MAKEWORD(2, 2), &wsaData);

    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr)); 
    servAddr.sin_family = PF_INET;  
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(1234); 
    bind(sock, (SOCKADDR*)&servAddr, sizeof(SOCKADDR));

    SOCKADDR clntAddr; 
    int nSize = sizeof(SOCKADDR);
    char buffer[BUF_SIZE]; 
    while(1)
	{
        int strLen = recvfrom(sock, buffer, BUF_SIZE, 0, &clntAddr, &nSize);
        sendto(sock, buffer, strLen, 0, &clntAddr, nSize);
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}