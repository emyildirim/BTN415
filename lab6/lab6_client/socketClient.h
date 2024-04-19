#pragma once
#include <string>
#include <iostream>
#include <winsock2.h>

#define MAX_BUFFER_SIZE 512

class Node {
protected:
	static bool dlls_started;
	static int num_nodes;
	std::string ip;
	std::string role;
	std::string protocol;
	int port;
	SOCKET active_socket;
public:
	Node();
	Node(std::string ip, int port);
	~Node();
	void start_dlls();
	bool create_socket();
	void display_info() const;
};

class Client_TCP : public Node {
public:
	Client_TCP();
	bool connect_socket(std::string ip, int port);
	int send_message(std::string message);
	int receive_message(std::string& message);
};