#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
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
        this->server_socket = socket(AF_INET, SOCK_STREAM, 0);
 
        // Bind the ip address and port to a socket
        sockaddr_in hint;
        hint.sin_family = AF_INET;
        hint.sin_port = htons(server_port);
        inet_pton(AF_INET, server_address.c_str(), &hint.sin_addr);
 
        bind(server_socket, (sockaddr*)&hint, sizeof(hint));
 
        // Tell Winsock the socket is for listening
        listen(server_socket, SOMAXCONN);

        fd_set master;
        FD_ZERO(&master);
        FD_SET(server_socket, &master);

        int client_socket;
        sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        while(runner){
            fd_set copy = master;
            int socket_count = select(0, &copy, nullptr, nullptr, nullptr);

            for(int i=0; i<socket_count; i++){
                if(FD_ISSET(i, &copy)){
                    if(i == server_socket){
                        client_socket = accept(server_socket, (sockaddr *) &client_addr, &client_len);
                        cout << "Received a Client" << endl;
                    }else{
                        cout << "Received Message!" << endl;
                    }
                }
            }
        }
    }
    thread retThread(){
        thread rtval([=]{establishConn();});
        return rtval;
    }
};