#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "socketClient.h"
#include <string>
#include <iostream>
#include <winsock2.h>
#include <stdlib.h>
#include "Bitfields.h"
#pragma comment(lib, "Ws2_32.lib")

bool Node::dlls_started = false;
int Node::num_nodes = 0;

Node::Node() {
    start_dlls();
    num_nodes++;
    this->active_socket = INVALID_SOCKET;
    this->protocol = "tcp";
    this->ip = "127.0.0.1";
    this->port = 27000;
}

Node::Node(std::string ip, int port) {
    start_dlls();
    num_nodes++;
    this->active_socket = INVALID_SOCKET;
    this->ip = ip;
    this->port = port;
}

Node::~Node() {
    closesocket(this->active_socket);
    std::cout << "Closing socket" << std::endl;
    num_nodes--;
    if (num_nodes == 0) {
        WSACleanup();
    }
}

void Node::start_dlls() {
    if (!dlls_started) {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cout << "Could not start DLLs" << std::endl;
            exit(EXIT_FAILURE);
        }
        else {
            dlls_started = true;
        }
    }
}

bool Node::create_socket() {
    if (this->protocol == "tcp") {
        this->active_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    }
    else {
        this->active_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    }

    if (this->active_socket == INVALID_SOCKET) {
        std::cout << "Could not create socket" << std::endl;
        return false;
    }
    else {
        std::cout << "Socket initialized\n";
        return true;
    }
}

void Node::display_info() const {
    std::cout << "IP: " << this->ip << std::endl;
    std::cout << "port: " << this->port << std::endl;
    std::cout << "protocol: " << this->protocol << std::endl;
    std::cout << "dlls: " << dlls_started << std::endl;
}

Client_TCP::Client_TCP() : Node() {
    this->protocol = "tcp";
    this->role = "client";
}

bool Client_TCP::connect_socket(std::string ip, int port) {
    struct sockaddr_in SvrAddr;
    SvrAddr.sin_family = AF_INET;
    SvrAddr.sin_port = htons(port);
    SvrAddr.sin_addr.s_addr = inet_addr(ip.c_str());
    if ((connect(this->active_socket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr))) == SOCKET_ERROR) {
        std::cout << "Failed to connect to server" << std::endl;
        return false;
    }
    else {
        std::cout << "Connection Established\n";
        return true;
    }
}

int Client_TCP::send_message(std::string message) {
    //calculate checksum of the message
    unsigned char checksum = crc(const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(message.c_str())), message.length());

    //convert checksum to string and append to the message
    message.push_back(static_cast<char>(checksum));

    //send the message with checksum
    return send(this->active_socket, message.c_str(), message.length(), 0);
}


int Client_TCP::receive_message(std::string& message) {
    char RxBuffer[MAX_BUFFER_SIZE] = {};
    int bytes = recv(this->active_socket, RxBuffer, MAX_BUFFER_SIZE, 0);

    if (bytes > 0) {
        //the last byte of the buffer is the checksum
        unsigned char received_checksum = static_cast<unsigned char>(RxBuffer[bytes - 1]);

        //calculate the checksum of the received message minus the checksum byte
        unsigned char calculated_checksum = crc(reinterpret_cast<unsigned char*>(RxBuffer), bytes - 1);

        if (calculated_checksum == received_checksum) {
            //checksum is correct, extract the message without the checksum byte
            message.assign(RxBuffer, bytes - 1);
        }
        else {
            std::cerr << "Checksum mismatch: Data may be corrupted." << std::endl;
            return -1; //checksum mismatch
        }
    }

    return bytes > 0 ? bytes - 1 : bytes;
}