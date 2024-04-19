#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <string>
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")

int main()
{
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

    // TODO: get lbs value on client and send to the server
    // Then receive it as kg from the server
    std::cout << "Enter a Weight (lbs): ";
    while (1) {
        //sends weight		
        double weightLbs = 0;
        std::cin >> weightLbs;
        if (std::cin.fail() || weightLbs <= 0) {
            // flush the buffer
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Enter a positive number (Weight/lbs): ";
        }
        else {
            send(ClientSocket, std::to_string(weightLbs).c_str(), static_cast<int>(std::to_string(weightLbs).size()), 0);
            break;
        }
    }

    char RxBuffer[128] = {};
    recv(ClientSocket, RxBuffer, sizeof(RxBuffer), 0);
    std::cout << "Response (Weight/kg): " << RxBuffer << std::endl;

    closesocket(ClientSocket);
    WSACleanup();

    return 0;
}






