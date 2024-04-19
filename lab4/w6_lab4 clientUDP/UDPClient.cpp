// UDPClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <chrono>
#pragma comment(lib, "Ws2_32.lib")

int main() {

    //Start the timer
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "starting...\n";

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "Could not start DLLs" << std::endl;
        return 0;
    }

    SOCKET ClientSocket;
    ClientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (ClientSocket == INVALID_SOCKET) {
        std::cout << "Could not create socket" << std::endl;
        WSACleanup();
        return 0;
    }

    struct sockaddr_in SvrAddr;
    SvrAddr.sin_family = AF_INET;
    SvrAddr.sin_port = htons(27020);
    SvrAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    
    //TODO: measure how long does UDP protocol take
    // for 100000 message sent and received
    int counter = 0;
    int iteration = 100000;
    while (counter < iteration) {
        char TxBuffer[128] = {};
        sendto(ClientSocket, TxBuffer, sizeof(TxBuffer), 0,
            (struct sockaddr*)&SvrAddr, sizeof(SvrAddr));

        char RxBuffer[128] = "Let's Go";
        int addr_len = sizeof(SvrAddr);
        recvfrom(ClientSocket, RxBuffer, sizeof(RxBuffer), 0,
            (struct sockaddr*)&SvrAddr, &addr_len);
        counter++;
    }

    closesocket(ClientSocket);
    WSACleanup();

    //End the timer
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "ended!\n";

    // Calculate the duration and print it
    std::chrono::duration<double> totalDuration = end - start;
    std::cout << "Result| Execution time: " << totalDuration.count() << " seconds" << '\n';
}


