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
        return ii;
    }
    std::string rtAddress() const{
        return address;
    }
    int rtPort() const{
        return port;
    }
};