#pragma once
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

class SERVER: public STRINGER{
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
    bool sendData(const int client_socket, string to_send,bool);
    string receiveData(const int);
    void establishConn();
    void close_connection();
    thread retThread();
};