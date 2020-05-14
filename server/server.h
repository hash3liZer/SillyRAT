#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>  
#include <sys/time.h>
#include <thread>

using namespace std;

class SERVER{
private:
    bool runner;
    string server_address;
    int server_port;
    int server_socket;
    int clients[SOMAXCONN];

public:
    SERVER(const string addr, const int pt){
        this->runner         = true;
        this->server_address = addr;
        this->server_socket  = 0;
        this->server_port    = pt;

        for(int i=0; i<SOMAXCONN; i++){
            clients[i] = 0;
        }
    }
    void setRunner(const bool val){
        runner = val;
    }
    void acceptor_thread(){
        while(runner){

        }
    }
    void establishConn(){
        int opt = 1;
        int max_fd;

        this->server_socket = socket(AF_INET, SOCK_STREAM, 0);
        setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
 
        // Bind the ip address and port to a socket
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

            for(int i=0; i<SOMAXCONN; i++){
                fd = clients[i];
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
                    cout << "Connectioned Received!" << endl;
                }
            }

            for(int i=0; i<SOMAXCONN; i++){
                if(clients[i] == 0){
                    clients[i] = client_socket;
                    break;
                }
            }
        }
    }
    thread retThread(){
        thread rtval([=]{establishConn();});
        return rtval;
    }
};