// EmailClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <iostream>
#include <string>

#pragma comment(lib, "Ws2_32.lib")
using namespace std;

int main()
{
	//starts Winsock DLLs
	WSADATA wsaData;
	if ((WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
		return 0;
	}

	//initializes socket. SOCK_STREAM: TCP
	SOCKET ClientSocket;
	ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ClientSocket == INVALID_SOCKET) {
		WSACleanup();
		return 0;
	}
	std::cout << "Client Socket Initialized: " << ClientSocket << std::endl;

	//Connect socket to specified server
	sockaddr_in SvrAddr;
	SvrAddr.sin_family = AF_INET;						//Address family type itnernet
	SvrAddr.sin_port = htons(27000);					//port (host to network conversion)
	SvrAddr.sin_addr.s_addr = inet_addr("127.0.0.1");	//IP address
	if ((connect(ClientSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr))) == SOCKET_ERROR) {
		closesocket(ClientSocket);
		WSACleanup();
		return 0;
	}
	std::cout << "Connection Established\n";

	//user inputs the username
	std::string username;
	std::cout << "Enter user name: ";
	std::getline(cin, username);
	
	//sends the username to the server
	send(ClientSocket, username.c_str(), static_cast<int>(username.size() + 1), 0);
	std::cout << "Username sent to the client!\nWaiting for response!\n" << endl;

	//receives the email related to the username
	char TxBuffer[1024] = {};
	int i = 0;
	while (i < 1) {
		recv(ClientSocket, TxBuffer, sizeof(TxBuffer), 0);
		i++;
	}
	std::cout << TxBuffer << '\n';
	
	//closes connection and socket
	closesocket(ClientSocket);
	//frees Winsock DLL resources
	WSACleanup();
}
