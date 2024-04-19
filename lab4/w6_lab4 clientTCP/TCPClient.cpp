#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <chrono>
#pragma comment(lib, "Ws2_32.lib")

int main()
{
    //Start the timer
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "starting...\n";

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "Could not start DLLs" << std::endl;
        return 0;
    }

    SOCKET ClientSocket;
    ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ClientSocket == INVALID_SOCKET) {
        std::cout << "Could not create socket" << std::endl;
        WSACleanup();
        return 0;
    }

    struct sockaddr_in SvrAddr;
    SvrAddr.sin_family = AF_INET;
    SvrAddr.sin_port = htons(27000);
    SvrAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if ((connect(ClientSocket, (struct sockaddr*)&SvrAddr,
        sizeof(SvrAddr))) == SOCKET_ERROR) {
        std::cout << "Failed to connect" << std::endl;
        closesocket(ClientSocket);
        WSACleanup();
        return 0;
    }

    //TODO: measure how long does TCP protocol take
    // for 100000 message sent and received
    int counter = 0;
    int iteration = 100000;
    while (counter < iteration) {
        char TxBuffer[128] = "Let's Go";
        send(ClientSocket, TxBuffer, sizeof(TxBuffer), 0);

        char RxBuffer[128] = {};
        recv(ClientSocket, RxBuffer, sizeof(RxBuffer), 0);
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

    return 0;
}






