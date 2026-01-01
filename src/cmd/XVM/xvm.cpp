/* UnSynk XMC Virtual Machine */
/* Version: 1.0.0 Pre-Alpha */
/* Created by UnSynk, tsesuv nostel */

#include "xvm.inc"
#include "core.inc"

////////////////////////////////////////////////////////

bool version(void);
bool help(void);

bool dbgprnt(void);

////////////////////////////////////////////////////////

int main(int ac, char **av)
{
	MEM mem;
	CPU cpu;
	Inst inst;
	InstInfo info;
	Exec exec;
	Core core;

	std::string args;
	for(int t = 0; t < ac; t++) args += std::string(av[t]) + " ";

	std::string ifname = "";
	std::string ofname = "";

	bool hasOut = false;

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

	if(!ofname.empty()) hasOut = true;

	core.init(1048576);

	while(core.power)
	{
		core.exeVM(1048576);

		cpu.setIRQ(!cpu.getIRQ(cpu.FLAG_R));
	}

	mem.free();

	return 0;
}

////////////////////////////////////////////////////////

bool version(void)
{
	return true;
}

bool help(void)
{
	return true;
}

bool dbgprnt(void)
{
	return true;
}
