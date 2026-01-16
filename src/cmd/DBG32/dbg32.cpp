/* UnSynk Debuger x86 Edition */
/* Version: 1.0.0 Pre-Alpha */
/* Created by UnSynk, tsesuv nostel */

#include "dbg32.inc"

////////////////////////////////////////////////////////

bool version(void);
bool help(void);

////////////////////////////////////////////////////////

int main(int ac, char **av)
{
	if(ac < 2) exit(!help());

	std::string args;
	for(int t = 0; t < ac; t++) args += std::string(av[t]) + " ";

	std::string ifname = "";

	std::regex i_patt(R"(/(?:i:|if=|infile:)([^\s/]+))");
	std::regex oth_patt1(R"(/(\?|help))");
	std::regex oth_patt2(R"(/(v|version))");
	std::smatch i_match;
	std::smatch oth_match1;
	std::smatch oth_match2;

	if(std::regex_search(args, i_match, i_patt)) ifname = i_match[1].str();
	if(std::regex_search(args, oth_match1, oth_patt1)) exit(!help());
	if(std::regex_search(args, oth_match2, oth_patt2)) exit(!version());

	return 0;
}

////////////////////////////////////////////////////////

bool version(void)
{
	std::cout << "UnSynk Debugger - A debugger trying respect DEBUG" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << " Version: 1.0.0 Pre-Alpha" << std::endl;
	std::cout << " Build: 2025122601" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << " Created by UnSynk, tsesuv notsel" << std::endl;
	std::cout << " Enter 'DBG32 /?` you get more helps." << std::endl;

	return true;
}

bool help(void)
{
	std::cout << "UnSynk Debugger - A debugger trying respect DEBUG" << std::endl;
	std::cout << "Created by UnSynk, tsesuv notsel" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << "Usage:" << std::endl;
	std::cout << "	DBG32 [/i:<file path>]" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << "	/i:<file path>  /if=<file path>  /infile:<file path>  :  Specify input file path." << std::endl;
	std::cout << "	/?  /help											  :  This help message." << std::endl;
	std::cout << "	/v  /version										  :  Print software infomations." << std::endl;

	return true;
}
