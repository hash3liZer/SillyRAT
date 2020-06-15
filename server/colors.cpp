#include <iostream>
#include <string>
#include <vector>
#include "colors.h"

void STRINGER::eraseSubStr(std::string& mainStr, const std::string& toErase){
	// Search for the substring in string
	size_t pos = mainStr.find(toErase);
 
	if (pos != std::string::npos)
	{
		// If found then erase it from string
		mainStr.erase(pos, toErase.length());
	}
}
std::string STRINGER::base64_encode(const std::string &in){
    std::string out;

    int val=0, valb=-6;
    for (uchar c : in) {
        val = (val<<8) + c;
        valb += 8;
        while (valb>=0) {
            out.push_back(b[(val>>valb)&0x3F]);
            valb-=6;
        }
    }
    if (valb>-6) out.push_back(b[((val<<8)>>(valb+8))&0x3F]);
    while (out.size()%4) out.push_back('=');
    return out;
}
std::string STRINGER::base64_decode(const std::string &in){
    std::string out;

    std::vector<int> T(256,-1);
    for (int i=0; i<64; i++) T[b[i]] = i;

    int val=0, valb=-8;
    for (uchar c : in) {
        if (T[c] == -1) break;
        val = (val<<6) + T[c];
        valb += 6;
        if (valb>=0) {
            out.push_back(char((val>>valb)&0xFF));
            valb-=8;
        }
    }
    return out;
}

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
