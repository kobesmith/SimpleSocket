#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib") 
#define BUF_SIZE 1024

int main(int argc, char* argv[]) 
{
	char *filename = "D:\\send.mp4"; 
	FILE *fp = fopen(filename, "rb"); 
	if (fp == NULL)
	{
		printf("Cannot open file, press any key to exit!\n");
		system("pause");
		exit(0);
	}

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET servSock = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_port = htons(1234);
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	listen(servSock, 20);

	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);

	char buffer[BUF_SIZE] = { 0 };  
	int nCount;
	while ((nCount = fread(buffer, 1, BUF_SIZE, fp)) > 0)
	{
		send(clntSock, buffer, nCount, 0);
	}
	shutdown(clntSock, SD_SEND); 
	recv(clntSock, buffer, BUF_SIZE, 0); 
	fclose(fp);

	closesocket(clntSock);
	closesocket(servSock);

	WSACleanup();

	system("pause");
	return 0;
}