#include <iostream>
#include <string>
#include <vector>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

typedef unsigned char uchar;             // Custom Data Type
const string TARGETIP = "127.0.0.1";      // SERVER Ip Address
const int    TARGETPO = 54000;          // SERVER Port Number

// Some Extended Methods for String
class STRINGER{
private:
	string b;

public:
	STRINGER(){
		this->b = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";//=
	}
	void erase(string &upper, const string lower){
		size_t pos = upper.find(lower);
		if (pos != std::string::npos){
			upper.erase(pos, lower.length());
		}
	}
	string base64_encode(const std::string &in){
		std::string out;

		int val = 0, valb = -6;
		for (uchar c : in) {
			val = (val << 8) + c;
			valb += 8;
			while (valb >= 0) {
				out.push_back(b[(val >> valb) & 0x3F]);
				valb -= 6;
			}
		}
		if (valb>-6) out.push_back(b[((val << 8) >> (valb + 8)) & 0x3F]);
		while (out.size() % 4) out.push_back('=');
		return out;
	}
	string base64_decode(const std::string &in){
		std::string out;

		std::vector<int> T(256, -1);
		for (int i = 0; i<64; i++) T[b[i]] = i;

		int val = 0, valb = -8;
		for (uchar c : in) {
			if (T[c] == -1) break;
			val = (val << 6) + T[c];
			valb += 6;
			if (valb >= 0) {
				out.push_back(char((val >> valb) & 0xFF));
				valb -= 8;
			}
		}
		return out;
	}
};

class PREDECESSOR{
private:
	string ex_error;

protected:
	SOCKET connection_sock;
	int    connection_conn;

public:
	PREDECESSOR(){
		ex_error = "Peaceful Exit";
	}
	void setError(const string val){
		ex_error = val;
	}
	string getError() const{
		return ex_error;
	}
	bool checkWSocket(const int val){
		bool rtval = true;
		if (val != 0){
			setError("Not able to Initialize Window Socket");
			rtval = false;
		}
		return rtval;
	}
	bool checkSSocket(const SOCKET val){
		bool rtval = true;
		if (val == INVALID_SOCKET){
			setError("Wasn't Able to Create Socket Instance!");
			rtval = false;
		}
		return rtval;
	}
	bool checkSConnection(const int val){
		bool rtval = true;
		if (val == SOCKET_ERROR){
			setError("Wasn't able to establish a connection with Server!");
			rtval = false;
		}
		return rtval;
	}
	bool checkRError(const int val){
		bool rtval = false;
		if (val == SOCKET_ERROR){
			setError("Error While Receiving Data!");
			rtval = true;
		}
		return rtval;
	}
	SOCKET init(){
		SOCKET rtval = socket(AF_INET, SOCK_STREAM, 0);
		return rtval;
	}
	void close(const SOCKET toclose){
		closesocket(toclose);
		WSACleanup();
	}
};

class CLIENT: public PREDECESSOR{
private:
	string sv_address;
	int sv_port;

	// Ip Structure
	sockaddr_in client_ip;

	// Extended Stringer
	STRINGER stringer;

public:
	CLIENT(const string vala, const int valb){
		sv_address = vala;
		sv_port    = valb;
	}
	void setClient(){
		client_ip.sin_family = AF_INET;
		client_ip.sin_port = htons(sv_port);
		inet_pton(AF_INET, sv_address.c_str(), &client_ip.sin_addr);
	}
	void clean(string &data){
		stringer.erase(data, "abigbreakhere");
	}
	string receive(){
		char buf[4096];
		int recv_conn;
		string converter = "";
		string byter = "";

		do{
			recv_conn = recv(connection_sock, buf, 4096, 0);
			if (recv_conn == 0){ // Connection Closed by Server
				converter = "closed";
				break;
			}else if (this->checkRError(recv_conn)){
				converter = "shutdown";
				break;
			}else{
				byter = buf;
				converter += byter;
			}
		} while (byter.find("abigbreakhere") == string::npos);
		// Run the loop as long as it doesn't have abigbreakhere

		return converter;
	}
	void execute(string command){
		if (command.find(":") != string::npos){  // Command Prompt
			
		}else{                                   // Silly Prompt
		
		}
	}
	bool launch(){
		string data;
		bool rtval = false;
		cout << "Interface Launched!" << endl;
		while (true){
			data = receive();
			cout << "Received this: " << endl;
			if (data == "closed"){
				rtval = false;
				break;
			}
			else if (data == "shutdown"){
				rtval = true;
				break;
			}
			else{
				clean(data);
				execute(data);
			}
		}
		return true;
	}
	void engage(){
		// Initialize WinSock
		WSAData data;
		WORD ver = MAKEWORD(2, 2);
		int ws_result = WSAStartup(ver, &data);

		if (this->checkWSocket(ws_result)){
			connection_sock = this->init();
			if (this->checkSSocket(connection_sock)){
				// Set Client
				setClient();

				// Connect to server
				while (true){
					cout << "Establishing!" << endl;
					connection_conn = connect(connection_sock, (sockaddr*)&client_ip, sizeof(client_ip));
					if (this->checkSConnection(connection_conn)){
						bool stopper = this->launch();
						if (stopper){
							break;
						}
					}
				}
				close(connection_sock);
			}
		}
	}
};

int main(){
	CLIENT SillyClient(TARGETIP, TARGETPO);
	SillyClient.engage();
	cout << SillyClient.getError() << endl;
	system("pause");
}
