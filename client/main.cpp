#include <iostream>
#include <string>
#include <Windows.h>
#include <WinInet.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

class CLIENT {
	int sock;
	int PORT;
	int readReceivedBytes;
	string ipAddress;
	string DataToBeSent;
	char receivedData[1024];
	struct sockaddr_in serverAddress;
public:
	CLIENT() {
		this->sock = 0;
		this->ipAddress = "127.0.0.1"; // Localhost
		this->PORT = 54000;
		checkConnection();
	}
	CLIENT(string ipAddress) {
		this->ipAddress = ipAddress;
		this->PORT=54000;
		checkConnection();
	}
	CLIENT(int PORT) {
		this->ipAddress = "127.0.0.1";
		this->PORT=PORT;
		if(PORT <= 0 || PORT > 65535)
			PORT = 54000;
		checkConnection();
	}
	CLIENT(string ipAddress, int PORT) {
		this->ipAddress = ipAddress;
		this->PORT = PORT;
		if(PORT <= 0 || PORT > 65535)
			PORT = 54000;
		checkConnection();
	}
	void setData(string ipAddress) {
		this->ipAddress = ipAddress;
		this->PORT = 54000;
		checkConnection();
	}
	void setData(int PORT) {
		this -> ipAddress = "127.0.0.1";
		this -> PORT = PORT;
		if(PORT <= 0 || PORT > 65535)
			PORT = 54000;
		checkConnection();
	}
	void setData(string ipAddress, int PORT) {
		this -> ipAddress = ipAddress;
		this -> PORT = PORT;
		if(PORT <= 0 || PORT > 65535)
			PORT = 54000;
		checkConnection();
	}
	void checkConnection() {
		if((sock = socket(AF_INET, SOCK_STREAM, 0) < 0)) {
			cout << "[!] Unable to create a socket!\n";
			errorQuit(-69);
		}
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_port = htons(PORT);
		if (connect(sock, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
			cout << "[!] Connection to " << this->ipAddress << " on PORT " << this->PORT << " failed!.";
			errorQuit(-200);
		}
	}
	void sendData(string DataToBeSent) {
		send(sock, DataToBeSent.c_str(), DataToBeSent.length(), 0);
		cout << "[+] Following data was sent to the server successfully: " << DataToBeSent << endl << endl;
	}
	void receiveData() {
		readReceivedBytes = recv(sock, receivedData, strlen(receivedData), 0);
		cout << "[+] Data Received From Server: " << receivedData;
	}
	void errorQuit(int errorCode) {
		cout << "\n[!] Program Failed with Error Code " << errorCode << endl;
		system("pause");
		exit(0);
	}
};

int main() {
	CLIENT s("182.176.65.4", 12000);
	s.sendData("Hello");
	s.receiveData();
	system("pause");
}