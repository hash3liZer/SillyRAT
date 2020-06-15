#include <iostream>
#include <string>
#include <cstring>
#include <climits>
#include "colors.h"

class INPUT{
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
    
    std::string reduce(const std::string& str, const std::string& fill = " ", const std::string& whitespace = " \t"){
        // trim first
        auto result = trim(str, whitespace);

        // replace sub ranges
        auto beginSpace = result.find_first_of(whitespace);
        while (beginSpace != std::string::npos){
            const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
            const auto range = endSpace - beginSpace;

            result.replace(beginSpace, range, fill);

            const auto newStart = beginSpace + fill.length();
            beginSpace = result.find_first_of(whitespace, newStart);
        }
        return result;
    }
};