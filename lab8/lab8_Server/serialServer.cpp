// serialServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include "socketServer.h"
#include "Email.h"
#pragma warning(disable : 4996)

int main() {
	//set memory allocation flags to detect the memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//load data
	std::vector<Email> emails;
	emails.push_back(Email("JobsS", EmailDetails("Bill", "Jobs", "Finance Presentation", "Looking forward to our meeting on finance")));
	emails.push_back(Email("BillG", EmailDetails("Warren", "Bill", "Dinner", "It was lovely meeting you over dinner meeting")));
	emails.push_back(Email("WarrenB", EmailDetails("Elon", "Warren", "SpaceX", "Hows new SpaceX project going?")));
	emails.push_back(Email("JobsS", EmailDetails("Elon", "Jobs", "Twitter", "How is it going at Twitter?")));

	Server_TCP server("127.0.0.1", 28000);

	server.create_socket();
	server.bind_socket();
	server.listen_for_connections();
	server.accept_connection();

	//receives the username from the client
	std::string recUsername;
	server.receive_message(recUsername);
	std::cout << "Username received from the client --> " << recUsername << '\n';

	//search and find the emails sent to the username
	std::string results;
	for (auto& email : emails) {
		if (std::strcmp(email.getUserName(), recUsername.c_str()) == 0) {
			results += email.emailDetailsToStr();
		}
	}

	//create a packet and set its info
	packet emailsPacket{};
	if (results.empty()) {
		std::string message = "No emails found for " + recUsername;
		prepare_packet(emailsPacket, "Inbox", static_cast<int>(message.size()), false, message.c_str());
	}
	else {
		prepare_packet(emailsPacket, "Inbox", static_cast<int>(results.size()), true, results.c_str());
	}
	//sends the emails to the client back 
	server.send_packet(emailsPacket);

	std::cout << "Sent User Inbox to the client!\n";
	delete[] emailsPacket.letters;
    return 0;
}