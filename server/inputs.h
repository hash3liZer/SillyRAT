#include <iostream>
#include <string>
#include <climits>

class INPUT{
private:
    COLORS color;
    std::string address;
    int port;

public:
    void getLogo(){
		std::cout << std::endl << color.DARKCYAN;
		std::cout << "  ====       //    == \\\\\\\\  ====== ======" << std::endl;
		std::cout << "//   \\\\      //    ==    ]] ==  ==   ||  " << std::endl;
		std::cout << "\\\\        =  //    ==    ]] ==  ==   ||  " << std::endl;
		std::cout << "  ====   === //    == ////  ======   ||  " << std::endl;
		std::cout << "     \\\\  === //    ==   \\\\  ==  ==   ||  " << std::endl;
		std::cout << " \\\\  //  === //    ==    \\\\ ==  ==   ||  " << std::endl;
		std::cout << "  ====   === ////// =    ]] ==  ==   ||  " << color.YELLOW << "v1.0 @hash3liZer/TheFlash2K" << color.END << std::endl << std::endl << std::endl;
	}
    void getAddress(){
        std::cout << color.DARKCYAN << "[?] " << color.END << "Enter Binding Address (0.0.0.0): ";
        std::getline(std::cin, this->address);
        std::cin.ignore(INT_MAX, '\n');
    }
    void getPort(){
        std::cout << color.DARKCYAN << "[?] " << color.END << "Enter Port Number (54000): ";
        std::cin >> this->port;
        std::cin.ignore(INT_MAX, '\n');
    }
    std::string rtAddress() const{
        return address;
    }
    int rtPort() const{
        return port;
    }
};