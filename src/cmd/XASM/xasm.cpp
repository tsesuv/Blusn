#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <cstdlib>
#include <cstdint>

class XASM
{
	private:
		std::vector<uint8_t> binary;
		uint32_t origin = 0;

	public:
		XASM(): origin(0) {}

		bool l_asmbl(const std::string &line)
		{
			if(line.empty() || line[0] == ';') return true;

			std::istringstream iss(line);
			std::string mnemo;
			iss >> mnemo;

			if(mnemo == "ORG")
			{
				iss >> std::hex >> origin;
				return true;
			}

			if(mnemo == "NOP")
			{
				binary.push_back(0x00);
				return true;
			}

			if(mnemo == "LD")
			{
				std::string dst;
				std::string src;
				iss >> dst;

				if(dst.back() == ',') dst.pop_back();
				else
				{
					char cma;
					iss >> cma;
				}

				iss >> src;

				binary.push_back(0x03);
			}

			if(mnemo == "HALT")
			{
				binary.push_back(0x0F);
				return true;
			}
		}

		bool asmblf(const std::string &fname)
		{
			std::ifstream file(fname);
			if(!file)
			{
				std::cerr << "[ ERROR ] XASM: asmblf: Cannnot open file: " << fname << std::endl;
				return false;
			}

			std::string line;
			int lpos = 1;
			while(std::getline(file, line))
			{
				if(!l_asmbl(line))
				{
					std::cerr << "[ ERROR ] XASM: asmblf: l_asmbl: Error at line " << lpos << std::endl;
					return false;
				}
				lpos++;
			}

			return true;
		}

		int w2f(const std::string &fname)
		{
			std::ofstream file(fname, std::ios::binary);
			file.write(reinterpret_cast<const char*>(binary.data()), binary.size());

			return 0;
		}

		// int asm_LdA2I(uint32_t imm)
		// {
		// 	binary.push_back(0x03);
		// 	binary.push_back(0x00);
		// 	binary.push_back(0x00);
			
		// 	binary.push_back(imm & 0xFF);
		// 	binary.push_back((imm >> 8) & 0xFF);
		// 	binary.push_back((imm >> 16) & 0xFF);
		// 	binary.push_back((imm >> 24) & 0xFF);

		// 	return 0;
		// }
};

bool help(void);

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		exit(!help());
	}

	std::string args;
	for(int t = 0; t < argc; t++)
	{
		args += std::string(argv[t]) + " ";
	}

	XASM asmbl;
	std::string ifname = "";
	std::string ofname = "";

	std::regex i_patt(R"(/(?:i:|if=|infile:)([^\s/]+))");
	std::regex o_patt(R"(/(?:o:|of=|outfile:)([^\s/]+))");
	std::smatch i_match;
	std::smatch o_match;
	if(std::regex_search(args, i_match, i_patt)) ifname = i_match[1].str();
	if(std::regex_search(args, o_match, o_patt)) ofname = o_match[1].str();

	if(asmbl.asmblf(ifname))
	{
		asmbl.w2f(ofname);
		return 0;
	}

	return 1;
}


bool help(void)
{
	std::cout << "XMC Assembler" << std::endl;
	std::cout << "Created by UnSynk, tsesuv notsel" << std::endl;
	std::cout << "Usage:" << std::endl;
	std::cout << "\t/i:<file path>  /if=<file path>  /infile:<file path>\t:\tSpecify input file path." << std::endl;
	std::cout << "\t/o:<file path>\t:\tSpecify output file path." << std::endl;

	return true;
}