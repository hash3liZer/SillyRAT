#include <iostream>
#include <string>

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

	COLORS(){

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
};