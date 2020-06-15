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
#include "server.h"

using namespace std;

SERVER::SERVER(const string addr, const int pt){
    this->runner         = true;
    this->server_address = addr;
    this->server_socket  = 0;
    this->server_port    = pt;
}
void SERVER::setRunner(const bool val){
    runner = val;
}
map<int, string> SERVER::retClients(){
    return client_sockets;
}
string SERVER::base64_encode(const std::string &in){
    std::string out;

    int val=0, valb=-6;
    for (uchar c : in) {
        val = (val<<8) + c;
        valb += 8;
        while (valb>=0) {
            out.push_back(b[(val>>valb)&0x3F]);
            valb-=6;
        }
    }
    if (valb>-6) out.push_back(b[((val<<8)>>(valb+8))&0x3F]);
    while (out.size()%4) out.push_back('=');
    return out;
}
string SERVER::base64_decode(const string &in){
    std::string out;

    std::vector<int> T(256,-1);
    for (int i=0; i<64; i++) T[b[i]] = i;

    int val=0, valb=-8;
    for (uchar c : in) {
        if (T[c] == -1) break;
        val = (val<<6) + T[c];
        valb += 6;
        if (valb>=0) {
            out.push_back(char((val>>valb)&0xFF));
            valb-=8;
        }
    }
    return out;
}
string SERVER::receiveData(const int client_socket){
    string rtval = "Timeout Occured! Didn't Received anything from the client!"; 
    bool status = false;
    for(int i=1; i <= 40; i++){
        for(messages_it=messages.begin(); messages_it != messages.end(); messages_it++){
            if(messages_it->first == client_socket){
                if(messages_it->second.length() > 0){
                    rtval = messages_it->second;
                    status = true;
                    break;
                }
            }
        }
        if(status){
            break;
        }
        sleep(1);
    }
    if(status){
        this->messages.erase(client_socket);
    }
    return rtval;
}
void SERVER::establishConn(){
    int opt = 1;
    int max_fd;

    this->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
 
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(server_port);
    inet_pton(AF_INET, server_address.c_str(), &hint.sin_addr);
 
    bind(server_socket, (sockaddr*)&hint, sizeof(hint));
    listen(server_socket, SOMAXCONN);

    int fd;
    int md;
    int client_read;
    char recv_buffer[4096];
    string recv_data;

    int client_socket = 0;
    sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    struct timeval tv;
    tv.tv_sec = 0.5;
    tv.tv_usec = 0;

    while(runner){
        FD_ZERO(&master);
        FD_SET(server_socket, &master);
        max_fd = server_socket;

        for(client_sockets_it=client_sockets.begin(); client_sockets_it != client_sockets.end(); client_sockets_it++){
            fd = client_sockets_it->first;
            if(fd > 0){
                FD_SET(fd, &master);
            }
            if(fd > max_fd){
                max_fd = fd;
            }
        }

        int socket_count = select(max_fd+1, &master, nullptr, nullptr, &tv);

        if(FD_ISSET(server_socket, &master)){
            client_socket = accept(server_socket, (sockaddr *) &client_addr, &client_len);
            if(client_socket > 0){
                if(client_sockets.count(client_socket) <= 0){
                    client_sockets.insert(std::pair<int, std::string>(client_socket, inet_ntoa(client_addr.sin_addr)));
                }
            }
        }else{
            for(client_sockets_it=client_sockets.begin(); client_sockets_it != client_sockets.end(); client_sockets_it++){
                if(FD_ISSET(client_sockets_it->first, &master)){
                    client_read = read(client_sockets_it->first, recv_buffer, 4095);
                    if(client_read == 0){
                        this->invalid_sockets.push_back(client_sockets_it->first);
                    }else{
                        recv_data = recv_buffer;
                        this->messages.insert(std::pair<int, std::string>(client_sockets_it->first, recv_data));
                    }
                    memset(recv_buffer, 0, sizeof(recv_buffer));
                    recv_data = "";
                }
            }
            // Removing Unwanted Sockets
            if(invalid_sockets.size() > 0){
                for(int i=0; i<invalid_sockets.size(); i++){
                    this->client_sockets.erase(invalid_sockets[i]);
                }
            }
        }
    }
}
void SERVER::close_connection(){
    close(this->server_socket);
}
thread SERVER::retThread(){
    thread rtval([=]{establishConn();});
    return rtval;
}