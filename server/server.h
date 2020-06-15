#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>  
#include <sys/time.h>
#include <vector>
#include <cstring>
#include <map>
#include <thread>
#include "colors.h"

using namespace std;
typedef unsigned char uchar;

// Base64 Encoding & Decoding
static const std::string b = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";//=

class SERVER{
private:
    bool runner;
    string server_address;
    int server_port;
    int server_socket;
    fd_set master;

    COLORS color;
    std::map<int, std::string> client_sockets;
    std::map<int, std::string>::iterator client_sockets_it;
    std::vector<int> invalid_sockets;

    std::map<int, std::string> messages;
    std::map<int, std::string>::iterator messages_it;

public:
    SERVER(const string, const int);
    void setRunner(const bool);
    map<int,string> retClients();
    string base64_encode(const string&);
    string base64_decode(const string&);
    bool sendData(const int client_socket, string to_send,bool cmd=false){
        string final_payload;
        string payload = this->base64_encode(to_send);
        if(cmd){
            final_payload = base64_encode("true") + ":" + payload;
        }else{
           final_payload = payload;
        }
        int status = send(client_socket, final_payload.c_str(), strlen(final_payload.c_str()), 0);
        if(status != 0){
            return true;
        }else{
            return false;
        }
    }
    string receiveData(const int);
    void establishConn();
    void close_connection();
    thread retThread();
};