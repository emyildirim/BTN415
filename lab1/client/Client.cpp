

//#include <windows.networking.sockets.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32")
#pragma warning(disable : 4996)

#include <iostream>
#include <string>
using namespace std;

int main()
{
	//starts Winsock DLLs
	WSADATA wsaData;
	if ((WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
		return 0;
	}

	//initializes socket. SOCK_STREAM: TCP
	SOCKET ClientSocket;
	ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ClientSocket == INVALID_SOCKET) {
		WSACleanup();
		return 0;
	}

	//Connect socket to specified server
	sockaddr_in SvrAddr;
	SvrAddr.sin_family = AF_INET;						//Address family type itnernet
	SvrAddr.sin_port = htons(27000);					//port (host to network conversion)
	SvrAddr.sin_addr.s_addr = inet_addr("127.0.0.1");	//IP address
	if ((connect(ClientSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr))) == SOCKET_ERROR) {
		closesocket(ClientSocket);
		WSACleanup();
		return 0;
	}


	//receives Rxbuffer
	
	// TODO: get lbs value on client and send to the server
	while (1) {
		//sends weight		
		double weightLbs = 0;
		std::cout << "Enter a Weight (lbs): " << endl;
		std::cin >> weightLbs;
		if (std::cin.fail() || weightLbs <= 0) {
			// flush the buffer
			std::cin.clear();
			std::cin.ignore(1000, '\n');
		}
		else {
			send(ClientSocket, std::to_string(weightLbs).c_str(), static_cast<int>(std::to_string(weightLbs).size()), 0);
		}
	}

	//closes connection and socket
	closesocket(ClientSocket);
	//frees Winsock DLL resources
	WSACleanup();
}