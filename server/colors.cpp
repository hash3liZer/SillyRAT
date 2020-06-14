#include <iostream>
#include <string>
#include <vector>
#include "colors.h"

COLORS::COLORS(){

	#ifdef __unix__
		WHITE = "\033[1m\033[0m";
		PURPLE = "\033[1m\033[95m";
		CYAN = "\033[1m\033[96m";
		DARKCYAN = "\033[1m\033[36m";
		BLUE = "\033[1m\033[94m";
		GREEN = "\033[1m\033[92m";
		YELLOW = "\033[1m\033[93m";
		RED = "\033[1m\033[91m";
		BOLD = "\033[1m";
		UNDERLINE = "\033[4m";
		END = "\033[0m";
		LINEUP = "\033[F";
	#else
		WHITE = "";
		PURPLE = "";
		CYAN = "";
		DARKCYAN = "";
		BLUE = "";
		GREEN = "";
		YELLOW = "";
		RED = "";
		BOLD = "";
		UNDERLINE = "";
		END = "";
		LINEUP = "";
	#endif
}

std::vector<std::string> COLORS::split(std::string text, const char sep=' '){
	std::vector<std::string> tokens;
	int start = 0, end = 0;
	while ((end = text.find(sep, start)) != std::string::npos) {
		tokens.push_back(text.substr(start, end - start));
		start = end + 1;
	}
	tokens.push_back(text.substr(start));
	return tokens;
}

void  COLORS::showLiner(const std::string addr, const int fd){
	if(addr.length() > 0){
		std::cout << this->YELLOW << "$" << this->END << " [" << this->RED << addr << ":" << fd << this->END << "] ";
	}else{
		std::cout << this->YELLOW << "$ " << this->END; 
	}
}
