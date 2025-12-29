/* UnSynk XMC Assembler */
/* Version: 1.0.0 Alpha */
/* Created by UnSynk, tsesuv nostel */

#include "xasm.inc"
#include "asmbl.inc"

////////////////////////////////////////////////////////

bool version(void);
bool help(void);

////////////////////////////////////////////////////////

int main(int ac, char **av)
{
	if(ac < 2) exit(!help());

	std::string args;
	for(int t = 0; t < ac; t++) args += std::string(av[t]) + " ";

	XASM asmbl;
	std::string ifname = "";
	std::string ofname = "";

	std::regex i_patt(R"(/(?:i:|if=|infile:)([^\s/]+))");
	std::regex o_patt(R"(/(?:o:|of=|outfile:)([^\s/]+))");
	std::regex oth_patt1(R"(/(\?|help))");
	std::regex oth_patt2(R"(/(v|version))");
	std::smatch i_match;
	std::smatch o_match;
	std::smatch oth_match1;
	std::smatch oth_match2;

	if(std::regex_search(args, i_match, i_patt)) ifname = i_match[1].str();
	if(std::regex_search(args, o_match, o_patt)) ofname = o_match[1].str();
	if(std::regex_search(args, oth_match1, oth_patt1)) exit(!help());
	if(std::regex_search(args, oth_match2, oth_patt2)) exit(!version());

	if(ifname.empty())
	{
		std::cerr << "[ERROR] XASM: No input file specified" << std::endl;
		return 1;
	}

	if(ofname.empty()) ofname = "a";

	if(asmbl.asmblf(ifname))
	{
		asmbl.w2f(ofname);
		return 0;
	}

	return 1;
}

bool version(void)
{
	std::cout << "====UnSynk XMC Assembler====" << std::endl;
	std::cout << " Version: 1.0.0 Alpha" << std::endl;
	std::cout << " Build: 2025122601" << std::endl;
	std::cout << "----------------------------------" << std::endl;
	std::cout << " Created by UnSynk, tsesuv notsel" << std::endl;
	std::cout << " Enter 'XASM /?` you get more helps." << std::endl;
	
	return true;
}

bool help(void)
{
	std::cout << "UnSynk XMC Assembler" << std::endl;
	std::cout << "Created by UnSynk, tsesuv notsel" << std::endl;
	std::cout << "Usage:" << std::endl;
	std::cout << "	XASM /i:<file path> [/o:<file path>]" << std::endl;
	std::cout << "Options:" << std::endl;
	std::cout << "	/i:<file path>  /if=<file path>  /infile:<file path>  :  Specify input file path." << std::endl;
	std::cout << "	/o:<file path>  /of=<file path>  /outfile:<file path> :  Specify output file path." << std::endl;
	std::cout << "	/?  /help                                             :  This help message." << std::endl;
	std::cout << "	/v  /version                                          :  Print software infomations." << std::endl;

	return true;
}
