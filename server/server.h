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
#include <map>
#include <thread>

using namespace std;

class SERVER{
private:
    bool runner;
    string server_address;
    int server_port;
    int server_socket;
    COLORS color;
    std::map<int, std::string> client_sockets;
    std::map<int, std::string>::iterator client_sockets_it;

public:
    SERVER(const string addr, const int pt){
        this->runner         = true;
        this->server_address = addr;
        this->server_socket  = 0;
        this->server_port    = pt;
    }
    void setRunner(const bool val){
        runner = val;
    }
    std::map<int, std::string> retClients(){
        return this->client_sockets;
    }
    void acceptor_thread(){
        while(runner){

        }
    }
    bool sendData(const int client_socket, string to_send){
        if(send(client_socket, to_send.c_str(), strlen(to_send.c_str()), 0) != strlen(to_send.c_str())){
            return false;
        }
        return true;
    }
    std::string receiveData(const int client_socket){
        return "";
    }
    void establishConn(){
        int opt = 1;
        int max_fd;

        this->server_socket = socket(AF_INET, SOCK_STREAM, 0);
        setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
 
        sockaddr_in hint;
        hint.sin_family = AF_INET;
        hint.sin_port = htons(server_port);
        inet_pton(AF_INET, server_address.c_str(), &hint.sin_addr);
 
        bind(server_socket, (sockaddr*)&hint, sizeof(hint));
 
        // Tell Winsock the socket is for listening
        listen(server_socket, SOMAXCONN);

        fd_set master;
        int fd;

        int client_socket;
        sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        struct timeval tv;
        tv.tv_sec = 2;
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

            int socket_count = select(max_fd+1, &master, nullptr, nullptr, nullptr);

            if(FD_ISSET(server_socket, &master)){
                client_socket = accept(server_socket, (sockaddr *) &client_addr, &client_len);
                if(client_socket >= 0){
                }
            }

            if(client_sockets.count(client_socket) <= 0){
                client_sockets.insert(std::pair<int, std::string>(client_socket, inet_ntoa(client_addr.sin_addr)));
            }
        }
    }
    thread retThread(){
        thread rtval([=]{establishConn();});
        return rtval;
    }
};