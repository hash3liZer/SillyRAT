#include<iostream>
#include<string>
#include"execute.h"
#include"client.h"

#pragma comment(lib, "ws2_32.lib")
using namespace std;

std::string TARGETIPADDRESS = "192.168.1.7";
int TARGETPORT = 54000;

class FRONTFACE{
private:
	string socket_address;
	int socket_port;

public:
	FRONTFACE(const string vala, const int valb){
		this->socket_address = vala;
		this->socket_port    = valb;
	}
	bool checkConnection(){
		WSADATA data;
		WORD versioner = MAKEWORD(2, 2);
		SOCKET test_socket;
		int ws_rtval = WSAStartup(versioner, &data);
		if(ws_rtval == 0){
			test_socket = socket(AF_INET, SOCK_STREAM, 0);
			if(test_socket != INVALID_SOCKET){
				closesocket(test_socket);
				WSACleanup();
				return true;
			}
		}
		closesocket(test_socket);
		WSACleanup();
		return false;
	}
	void engageClient(){
		if(this->checkConnection()){
			cout << "Binding to " << this->socket_address << ":" << this->socket_port << endl;
			CLIENT *client_conn = new CLIENT(this->socket_address, this->socket_port);
			client_conn->establishClient();
			cout << "Out of Game Now!" << endl;
		}
	}
};

//int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd){
int main(){
	FRONTFACE SillyClient(TARGETIPADDRESS, TARGETPORT);

	SillyClient.engageClient();

	system("pause");
}