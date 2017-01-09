#include <stdio.h>
#include <winsock2.h>

#pragma comment (lib, "ws2_32.lib")  
#define BUF_SIZE 100

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr)); 
	sockAddr.sin_family = PF_INET; 
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	sockAddr.sin_port = htons(1234);  
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	listen(servSock, 20);

	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	char buffer[BUF_SIZE] = { 0 }; 
	SOCKET clntSock; 
	while (1)
	{
		clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize); 
		int strLen = recv(clntSock, buffer, BUF_SIZE, 0);
		send(clntSock, buffer, strLen, 0); 

		closesocket(clntSock); 
		memset(buffer, 0, BUF_SIZE); 
	}

	closesocket(clntSock);
	closesocket(servSock);

	WSACleanup();
	return 0;
}