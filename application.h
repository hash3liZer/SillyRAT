#include<iostream>

using namespace std;

class SERVER{
protected:
    string sockAddr;
    int port;
}

class APPLICATION : public SERVER{
public:
    APPLICATION(){
        this->sockAddr = "127.0.0.1";
        this->port     = 1876;
    }
    APPLICATION(const string sockAddr){
        this->sockAddr = sockAddr;
        this->port     = 1876;
    }
    APPLICATION(const int port){
        this->sockAddr = "127.0.0.1";
        this->port     = 1876;
    }
    APPLICATION(const string sockAddr, const int port){
        this->sockAddr = sockAddr;
        this->port     = port;
    }



}