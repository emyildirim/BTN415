// EmailServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <vector>
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
#include "Email.h"
using namespace std;

int main()
{
	//load data
	std::vector<Email> emails;
	emails.push_back(Email("JobsS", EmailDetails("Bill", "Jobs", "Finance Presentation", "Looking forward to our meeting on finance")));
	emails.push_back(Email("BillG", EmailDetails("Warren", "Bill", "Dinner", "It was lovely meeting you over dinner meeting")));
	emails.push_back(Email("WarrenB", EmailDetails("Elon", "Warren", "SpaceX", "Hows new SpaceX project going?")));
	emails.push_back(Email("JobsS", EmailDetails("Elon", "Jobs", "Twitter", "How is it going at Twitter?")));


	//starts Winsock DLLs		
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	//create server socket
	SOCKET ServerSocket;
	ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ServerSocket == INVALID_SOCKET) {
		WSACleanup();
		return 0;
	}
	std::cout << "Socket Initialized\n";

	//binds socket to address
	sockaddr_in SvrAddr;
	SvrAddr.sin_family = AF_INET;
	SvrAddr.sin_addr.s_addr = INADDR_ANY;
	SvrAddr.sin_port = htons(27000);
	if (bind(ServerSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr)) == SOCKET_ERROR)
	{
		closesocket(ServerSocket);
		WSACleanup();
		return 0;
	}
	std::cout << "Socket bound successful\n";

	//listen on a socket
	if (listen(ServerSocket, 1) == SOCKET_ERROR) {
		closesocket(ServerSocket);
		WSACleanup();
		return 0;
	}
	std::cout << "Listening on Socket\n\n";

	//accepts a connection from a client
	SOCKET ConnectionSocket;
	ConnectionSocket = SOCKET_ERROR;
	if ((ConnectionSocket = accept(ServerSocket, NULL, NULL)) == SOCKET_ERROR) {
		closesocket(ServerSocket);
		WSACleanup();
		return 0;
	}
	cout << "Connection Established" << endl;
	
	//receives the username from the client
	char RxBuffer[50] = {};
	recv(ConnectionSocket, RxBuffer, sizeof(RxBuffer), 0);
	std::string recUsername = RxBuffer;
	std::cout <<"Username received from the client --> "<< recUsername << '\n';
	
	//search and find the emails sent to the username
	std::string results;
	for (auto& email : emails) {
		if (email.getTo() == recUsername) {
			results += email.display();
		}
	}

	if (results.empty()) {
		results = "No emails found for " + recUsername;
	}
	//sends the emails to the client back 
	send(ConnectionSocket, results.c_str(), static_cast<int>(results.size() + 1), 0);
	std::cout << "Sent User Inbox to the client!\n";

	closesocket(ConnectionSocket);	//closes incoming socket
	closesocket(ServerSocket);	    //closes server socket	
	WSACleanup();					//frees Winsock resources
}