#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <windows.h>
#include <WinInet.h>
#include <WinSock.h>
#include <iphlpapi.h>
#include <iostream>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

class CLIENT{
private:
	int ws_rtval;
	SOCKET client_socket;
	string socket_address;
	int socket_port;
	sockaddr_in socket_address_struct;

public:
	CLIENT(string addr, int port){
		this->socket_address = addr;
		this->socket_port = port;
		this->socket_address_struct.sin_family = AF_INET;
		this->socket_address_struct.sin_port   = htons(this->socket_port);

	}
	void establishClient(){
		WSADATA data;
		WORD versioner = MAKEWORD(2, 2);
		this->ws_rtval = WSAStartup(versioner, &data);
		if(ws_rtval == 0){
			this->client_socket = socket(AF_INET, SOCK_STREAM, 0);
			while(true){
				if(this->client_socket != INVALID_SOCKET){
					cout << "Successful up until now!" << endl;
					break;
				}else{
					cout << "Failed here" << endl;
					break;
				}
			}
		}
		cout << "Closing Socket!" << endl;
		closesocket(this->client_socket);
		WSACleanup();
	}
};