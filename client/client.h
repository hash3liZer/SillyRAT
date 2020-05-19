#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#pragma once

#define _WINSOCKAPI_
#include <iostream>
#include <string>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

class CLIENT {
private:
	int ws_rtval;
	SOCKET client_socket;
	string socket_address;
	int socket_port;
	sockaddr_in socket_address_struct;
	short int retries;

public:
	CLIENT(string addr, int port) {
		this->socket_address = addr;
		this->socket_port = port;
		this->socket_address_struct.sin_family = AF_INET;
		this->socket_address_struct.sin_port = htons(this->socket_port);
		inet_pton(AF_INET, socket_address.c_str(), &socket_address_struct.sin_addr);
		this->retries = 0;
	}
	void establishClient() {
		WSADATA data;
		int socket_connection;
		WORD versioner = MAKEWORD(2, 2);
		this->ws_rtval = WSAStartup(versioner, &data);
		if (ws_rtval == 0) {
			this->client_socket = socket(AF_INET, SOCK_STREAM, 0);
			while (true) {
				if (this->client_socket != INVALID_SOCKET) {
					socket_connection = connect(this->client_socket,
													(sockaddr *) &socket_address_struct,
													sizeof(socket_address_struct)
												);
					if (socket_connection != SOCKET_ERROR){
						retries = 0;
						this->launch();
					}else {
						cout << "Retrying" << endl;
						Sleep(3000);
						if (this->retries > 30) {
							break;
						}
						this->retries += 1;
					}
				}
				else {
					cout << "Failed here" << endl;
					break;
				}
			}
		}
		cout << "Closing Socket!" << endl;
		closesocket(this->client_socket);
		WSACleanup();
	}
	void launch(){
		PROMPT prompt;
		prompt.engage(this->client_socket);
	}
};