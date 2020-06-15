#include <iostream>
#include <string>
#include <vector>

#ifndef COLORS_H
#define COLORS_H

// Base64 Encoding & Decoding

typedef unsigned char uchar;
static const std::string b = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

class STRINGER{
public:
	std::string base64_encode(const std::string&);
    std::string base64_decode(const std::string&);
	void eraseSubStr(std::string&, const std::string&);
};

class COLORS{
public:
	std::string WHITE;
	std::string PURPLE;
	std::string CYAN;
	std::string DARKCYAN;
	std::string BLUE;
	std::string GREEN;
	std::string YELLOW;
	std::string RED;
	std::string BOLD;
	std::string UNDERLINE ;
	std::string END;
	std::string LINEUP;

	COLORS();
	std::vector<std::string> split(std::string, const char);
	void showLiner(const std::string, const int);
};

#endif