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

class Server_TCP : public Node {
private:
	SOCKET client_socket;
public:
	Server_TCP();
	Server_TCP(std::string ip, int port);
	~Server_TCP();
	bool bind_socket();
	bool listen_for_connections();
	bool accept_connection();
	int send_message(std::string message);
	int receive_message(std::string& message);
	void close_connection();
};