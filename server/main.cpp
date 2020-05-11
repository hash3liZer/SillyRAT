#include <iostream>
#include <string>
#include "colors.h"

using namespace std;

class CONNECTION{
protected:
	string sockAddr;
	int port;

public:
	void listen();
	void connect();
	void bind();
};

class SERVER: public CONNECTION{
private:
	COLORS color;

public:
	// Constuction
	SERVER(){
        this->sockAddr = "127.0.0.1";
        this->port     = 1876;
    }
    SERVER(const string sockAddr){
        this->sockAddr = sockAddr;
        this->port     = 1876;
    }
    SERVER(const int port){
        this->sockAddr = "127.0.0.1";
        this->port     = 1876;
    }
    SERVER(const string sockAddr, const int port){
        this->sockAddr = sockAddr;
        this->port     = port;
    }

	void initiate(){
		cout << "\t\t****************************" << endl;
		cout << "\t\t****************************" << endl;
		cout << "\t\t          SillyRAT          " << endl;
		cout << "\t\t****************************" << endl;
		cout << "\t\t****************************" << endl << endl;
	}

	bool bind(){
		
	}

	void engage(){
		cout << color.DARKCYAN << "[>] " << color.END << "Binding to ADDRESS: " << color.DARKCYAN << this->sockAddr << ":" << this->port << endl;
		if(!(bind())){
			
		}else{
			cout << color.RED << "[~] " << color.END << "Binding Failed. Check Your Address:Port" << endl;
		}
	}
};

int main(){
	SERVER SillyServer;

	SillyServer.initiate();
	SillyServer.engage();

	system("pause");
}