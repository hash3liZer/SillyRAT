#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "colors.h"
#include "inputs.h"

using namespace std;

class SERVER{
private:
	COLORS color;
	string sockAddr;
	int port;

public:
	// Constuction
	SERVER(){
        this->sockAddr = "0.0.0.0";
        this->port     = 54000;
    }
    SERVER(const string sockAddr){
        this->sockAddr = sockAddr;
        this->port     = 54000;
    }
    SERVER(const int port){
        this->sockAddr = "0.0.0.0";
        this->port     = port;
    }
    SERVER(const string sockAddr, const int port){
        this->sockAddr = sockAddr;
        this->port     = port;
    }

	// Variable Setter
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
				return true;
			}
		}
		return false;
	}

	void engageServer(){
		cout << color.DARKCYAN << "[>] " << color.END << "Binding to ADDRESS: " << color.DARKCYAN << this->sockAddr << ":" << this->port << endl;
		if((checkConnection())){
			
		}else{
			cout << color.RED << "[~] " << color.END << "Binding Failed. Check Your Address:Port" << endl;
		}
	}
};

int main(int argc, char* argv[]){
	INPUT svInputs;

	svInputs.getLogo();
	svInputs.getAddress();
	svInputs.getPort();
	
	if(svInputs.rtAddress() != "" && svInputs.rtPort() != 0){
		SERVER SillyServer(svInputs.rtAddress(), svInputs.rtPort());
	}else if(svInputs.rtAddress() != ""){
		SERVER SillyServer(svInputs.rtAddress());
	}else if(svInputs.rtPort() != 0){
		SERVER SillyServer(svInputs.rtPort());
	}else{
		SERVER SillyServer;
	}

	#ifdef SillyServer
	SillyServer.engageServer();
	#endif
}