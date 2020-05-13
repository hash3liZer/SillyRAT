#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <thread>
#include "colors.h"
#include "inputs.h"
#include "interface.h"
#include "server.h"

using namespace std;

class UPFRONT{
private:
	COLORS color;
	string sockAddr;
	int serverSocket;
	int port;

public:
	// Constuction
	UPFRONT(){
        this->sockAddr = "0.0.0.0";
        this->port     = 54000;
    }

	// Variable Setters
	void setVars(const string sockAddr){
        this->sockAddr = sockAddr;
        this->port     = 54000;
    }
    void setVars(const int port){
        this->sockAddr = "0.0.0.0";
        this->port     = port;
    }
	void setVars(const string addr, const int port){
		this->sockAddr = addr;
		this->port     = port;
	}

	bool checkConnection(){
		int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (serverSocket >= 0){
			sockaddr_in ipFam;
			ipFam.sin_family = AF_INET;
			ipFam.sin_port   = htons(this->port);
			inet_pton(AF_INET, sockAddr.c_str(), &ipFam.sin_addr);

			if(bind(serverSocket, (struct sockaddr *) &ipFam, sizeof(ipFam)) == 0){
				close(serverSocket);
				return true;
			}
		}
		close(serverSocket);
		return false;
	}

	void interfaceSv(){
		cout << color.DARKCYAN << "[>] " << color.END << "Here's Your Terminal. Enter 'help' to show available Commands" << endl;
		cout << endl;
		INTERFACE irface(this->sockAddr, this->port);
		irface.engage();
	}

	void engageServer(){
		cout << color.DARKCYAN << "[>] " << color.END << "Binding to ADDRESS: " << color.DARKCYAN << this->sockAddr << ":" << this->port << color.END << endl;
		if((this->checkConnection())){
			SERVER *server_conn = new SERVER(this->sockAddr, this->port);
			thread server_conn_thread = server_conn->retThread();
			
			this->interfaceSv();
			
			server_conn_thread.join();
		}else{
			cout << color.RED << "[~] " << color.END << "Binding Failed. Check Your Address:Port" << endl;
		}
	}
};

int main(int argc, char* argv[]){
	INPUT svInputs;
	UPFRONT SillyServer;

	svInputs.getLogo();
	svInputs.getAddress();
	svInputs.getPort();
	
	if(svInputs.rtAddress() != "" && svInputs.rtPort() != 0){
		SillyServer.setVars(svInputs.rtAddress(), svInputs.rtPort());
	}else if(svInputs.rtAddress() != ""){
		SillyServer.setVars(svInputs.rtAddress());
	}else if(svInputs.rtPort() != 0){
		SillyServer.setVars(svInputs.rtPort());
	}

	SillyServer.engageServer();
}