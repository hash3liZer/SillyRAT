#include <iostream>
#include <string>
#include <cstring>
#include <climits>
#include "colors.h"

class INPUT: public STRINGER{
private:
    COLORS color;
    std::string address;
    int port;

public:
    void getLogo();
    void getServerHelp();
    void getPort();
    void getAddress();
    std::string getInput();
    std::string rtAddress() const;
    int rtPort() const;
    // Utilities
    std::string trim(const std::string&, const std::string&);
    //std::string reduce(const std::string& str, const std::string& fill = " ", const std::string& whitespace = " \t")
    std::string reduce(const std::string&, const std::string&, const std::string&);
    // Removing a Subtring
    std::string eraseSubStr(std::string&, const std::string&);
};