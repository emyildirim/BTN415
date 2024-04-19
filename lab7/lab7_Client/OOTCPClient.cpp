// OOTCPClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string>
#include "socketClient.h"

int main() {
	
	Client_TCP client;
	client.create_socket();
	client.connect_socket("127.0.0.1", 28000);

	//user inputs the username
	std::string username;
	std::cout << "Enter user name: ";
	std::getline(std::cin, username);

	//sends the username to the server
	client.send_message(username);
	std::cout << "Username sent to the server!\nWaiting for response!\n" << std::endl;

	//receives the email related to the username
	std::string recMessage;
	client.receive_message(recMessage);
	std::cout << recMessage << std::endl;


	//USE DISPLAY INFO FUNC

	return 0;
}