// serialClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "socketClient.h"

int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
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

	packet received_packet;
	client.receive_packet(received_packet);
	std::cout << received_packet.name << " received\n\n";

	for (int i = 0; i < received_packet.size; i++){
		std::cout << received_packet.letters[i];
	}
	std::cout << std::endl;
	
    return 0;
}