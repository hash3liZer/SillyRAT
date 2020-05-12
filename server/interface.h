#include <iostream>
#include <string>

using namespace std;

class INTERFACE{
private:
    string inputSv;
    string sockAddr;
    int port;

    COLORS colorIf;
    INPUT inputIf;

public:
    INTERFACE(){
        this->inputSv  = "";
        this->sockAddr = "0.0.0.0";
        this->port     = 54000;
    }
    INTERFACE(const string vala, const int valb){
        this->inputSv  = "";
        this->sockAddr = vala;
        this->port     = valb;
    }
    void engage(){
        while(true){
            cout << colorIf.YELLOW << "$ " << colorIf.END ;
            this->inputSv = this->inputIf.getInput();

            if(this->inputSv == "exit"){
                break;
            }else if(this->inputSv == "help"){
                this->inputIf.getServerHelp();
            }
        }
    }
};