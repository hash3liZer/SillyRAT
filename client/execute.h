#pragma once
#define _WINSOCKAPI_
#include<iostream>
#include<string>
#include <WS2tcpip.h>
#include<windows.h>

using namespace std;

class PROMPT{
private:
	string result;
	char recv_buffer[4096];
public:
	void engage(SOCKET sock){
		int data_recv;
		do {
			ZeroMemory(recv_buffer, 4096);
			data_recv = recv(sock, this->recv_buffer, 4095, 0);
			if (data_recv > 0) {
				this->result = (string)recv_buffer;
				cout << this->result << endl;
				send(sock, "Data Going", sizeof("Data Going"), 0);
			}
		} while (result != "close" || result != "");
	}
};