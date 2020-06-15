#include <iostream>
#include <string>
#include <vector>

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