#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")  //╪сть ws2_32.dll

#define BUF_SIZE 10

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_port = htons(1234);

	char bufSend[BUF_SIZE] = { 0 };
	char bufRecv[BUF_SIZE] = { 0 };
	while (1) 
	{
		SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
		printf("Input a string: ");
		gets_s(bufSend);
		send(sock, bufSend, strlen(bufSend), 0);
		recv(sock, bufRecv, BUF_SIZE, 0);

		printf("Message form server: %s\n", bufRecv);

		memset(bufSend, 0, BUF_SIZE);  
		memset(bufRecv, 0, BUF_SIZE); 
		closesocket(sock);  
	}

	WSACleanup();

	system("pause");
	return 0;
}