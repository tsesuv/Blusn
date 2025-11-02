#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <map>
#include <sstream>
#include <cstdlib>
#include <cstdint>
#include <cctype>

////////////////////////////////////////////////////////

struct ISANode
{
	std::string mnemo; // "LD EAX, EBX" のような完全なニーモニック
	std::vector<uint8_t> opcode; // このノードまでのオペコード列
	std::map<uint8_t, ISANode*> children; // 次のバイト値 -> 子ノード
	bool is_term; // 命令の終端か
	int immSize; // 即値のバイト数（0なら即値なし）

	ISANode(): is_term(false), immSize(0) {}
	
	~ISANode()
	{
		for(auto &pair : children)
		{
			delete pair.second;
		}
	}
};

////////////////////////////////////////////////////////

class XASM
{
	private:
		std::vector<uint8_t> binary;
		uint32_t origin = 0;
		ISANode *isaR;

		void buildTree(void)
		{
			isaR = new ISANode();

			// NOP
			addInst(isaR, {0x00}, "NOP", 0);

			// INC系
			addInst(isaR, {0x01, 0x00, 0x00}, "INC EAX", 0);
			addInst(isaR, {0x01, 0x00, 0x01}, "INC EBX", 0);
			addInst(isaR, {0x01, 0x00, 0x02}, "INC [EBX]", 0);
			addInst(isaR, {0x01, 0x00, 0x03}, "INC ECX", 0);
			addInst(isaR, {0x01, 0x00, 0x04}, "INC EDX", 0);
			addInst(isaR, {0x01, 0x00, 0x05}, "INC EEX", 0);
			addInst(isaR, {0x01, 0x00, 0x06}, "INC EDI", 0);

			// ADD系
			// ADD EAX, ...
			addInst(isaR, {0x01, 0x01, 0x00, 0x00}, "ADD EAX, IMM", 4);
			addInst(isaR, {0x01, 0x01, 0x00, 0x01}, "ADD EAX, EBX", 0);
			addInst(isaR, {0x01, 0x01, 0x00, 0x02}, "ADD EAX, ECX", 0);
			addInst(isaR, {0x01, 0x01, 0x00, 0x03}, "ADD EAX, EDX", 0);
			addInst(isaR, {0x01, 0x01, 0x00, 0x04}, "ADD EAX, EEX", 0);

			// ADD EBX, ...
			addInst(isaR, {0x01, 0x01, 0x01, 0x00}, "ADD EBX, IMM", 4);
			addInst(isaR, {0x01, 0x01, 0x01, 0x01}, "ADD EBX, EAX", 0);
			addInst(isaR, {0x01, 0x01, 0x01, 0x02}, "ADD EBX, ECX", 0);
			addInst(isaR, {0x01, 0x01, 0x01, 0x03}, "ADD EBX, EDX", 0);
			addInst(isaR, {0x01, 0x01, 0x01, 0x04}, "ADD EBX, EEX", 0);
			addInst(isaR, {0x01, 0x01, 0x01, 0x05}, "ADD [EBX], IMM", 4);
			addInst(isaR, {0x01, 0x01, 0x01, 0x06}, "ADD [EBX], EAX", 0);
			addInst(isaR, {0x01, 0x01, 0x01, 0x07}, "ADD [EBX], ECX", 0);
			addInst(isaR, {0x01, 0x01, 0x01, 0x08}, "ADD [EBX], EDX", 0);
			addInst(isaR, {0x01, 0x01, 0x01, 0x09}, "ADD [EBX], EEX", 0);

			// LD系
			// LD EAX, ...
			addInst(isaR, {0x03, 0x00, 0x00}, "LD EAX, IMM", 4);
			addInst(isaR, {0x03, 0x00, 0x01}, "LD EAX, EBX", 0);
			addInst(isaR, {0x03, 0x00, 0x02}, "LD EAX, ECX", 0);
			addInst(isaR, {0x03, 0x00, 0x03}, "LD EAX, EDX", 0);
			addInst(isaR, {0x03, 0x00, 0x04}, "LD EAX, EEX", 0);
			addInst(isaR, {0x03, 0x00, 0x05}, "LD EAX, [IMM]", 4);
			addInst(isaR, {0x03, 0x00, 0x06}, "LD EAX, [EBX]", 0);
			addInst(isaR, {0x03, 0x00, 0x07}, "LD EAX, [EDI]", 0);
			addInst(isaR, {0x03, 0x00, 0x08}, "LD EAX, [ESI]", 0);
			addInst(isaR, {0x03, 0x00, 0x09}, "LD EAX, [EBP]", 0);
			addInst(isaR, {0x03, 0x00, 0x0A}, "LD [EAX], IMM", 4);
			addInst(isaR, {0x03, 0x00, 0x0B}, "LD [EAX], EBX", 0);
			addInst(isaR, {0x03, 0x00, 0x0C}, "LD [EAX], ECX", 0);
			addInst(isaR, {0x03, 0x00, 0x0D}, "LD [EAX], EDX", 0);
			addInst(isaR, {0x03, 0x00, 0x0E}, "LD [EAX], EEX", 0);
			addInst(isaR, {0x03, 0x00, 0x0F}, "LD [EAX], EDI", 0);
			addInst(isaR, {0x03, 0x00, 0x10}, "LD [EAX], EBP", 0);

			// LD EBX, ...
			addInst(isaR, {0x03, 0x01, 0x00}, "LD EBX, IMM", 4);
			addInst(isaR, {0x03, 0x01, 0x01}, "LD EBX, EAX", 0);
			addInst(isaR, {0x03, 0x01, 0x02}, "LD EBX, ECX", 0);
			addInst(isaR, {0x03, 0x01, 0x03}, "LD EBX, EDX", 0);
			addInst(isaR, {0x03, 0x01, 0x04}, "LD EBX, EEX", 0);
			addInst(isaR, {0x03, 0x01, 0x05}, "LD EBX, [IMM]", 4);
			addInst(isaR, {0x03, 0x01, 0x06}, "LD EBX, [EDI]", 0);
			addInst(isaR, {0x03, 0x01, 0x07}, "LD EBX, [ESI]", 0);
			addInst(isaR, {0x03, 0x01, 0x08}, "LD EBX, [EBP]", 0);
			addInst(isaR, {0x03, 0x01, 0x09}, "LD [EBX], IMM", 4);
			addInst(isaR, {0x03, 0x01, 0x0A}, "LD [EBX], EAX", 0);
			addInst(isaR, {0x03, 0x01, 0x0B}, "LD [EBX], ECX", 0);
			addInst(isaR, {0x03, 0x01, 0x0C}, "LD [EBX], EDX", 0);
			addInst(isaR, {0x03, 0x01, 0x0D}, "LD [EBX], EEX", 0);
			addInst(isaR, {0x03, 0x01, 0x0E}, "LD [EBX], EDI", 0);
			addInst(isaR, {0x03, 0x01, 0x0F}, "LD [EBX], ESI", 0);
			addInst(isaR, {0x03, 0x01, 0x10}, "LD [EBX], EBP", 0);

			// LD ECX, ...
			addInst(isaR, {0x03, 0x02, 0x00}, "LD ECX, IMM", 4);
			addInst(isaR, {0x03, 0x02, 0x01}, "LD ECX, EAX", 0);
			addInst(isaR, {0x03, 0x02, 0x02}, "LD ECX, EBX", 0);
			addInst(isaR, {0x03, 0x02, 0x03}, "LD ECX, EDX", 0);
			addInst(isaR, {0x03, 0x02, 0x04}, "LD ECX, EEX", 0);

			// LD EDX, ...
			addInst(isaR, {0x03, 0x03, 0x00}, "LD EDX, IMM", 4);
			addInst(isaR, {0x03, 0x03, 0x01}, "LD EDX, EAX", 0);
			addInst(isaR, {0x03, 0x03, 0x02}, "LD EDX, EBX", 0);
			addInst(isaR, {0x03, 0x03, 0x03}, "LD EDX, ECX", 0);
			addInst(isaR, {0x03, 0x03, 0x04}, "LD EDX, EEX", 0);

			// LD EEX, ...
			addInst(isaR, {0x03, 0x04, 0x00}, "LD EEX, IMM", 4);
			addInst(isaR, {0x03, 0x04, 0x01}, "LD EEX, EAX", 0);
			addInst(isaR, {0x03, 0x04, 0x02}, "LD EEX, EBX", 0);
			addInst(isaR, {0x03, 0x04, 0x03}, "LD EEX, ECX", 0);
			addInst(isaR, {0x03, 0x04, 0x04}, "LD EEX, EDX", 0);

			// CALL系
			addInst(isaR, {0x0C, 0x00}, "CALL EAX", 0);
			addInst(isaR, {0x0C, 0x01}, "CALL EBX", 0);
			addInst(isaR, {0x0C, 0x02}, "CALL ECX", 0);
			addInst(isaR, {0x0C, 0x03}, "CALL EDX", 0);
			addInst(isaR, {0x0C, 0x04}, "CALL EEX", 0);

			// RET, HALT
			addInst(isaR, {0x0E}, "RET", 0);
			addInst(isaR, {0x0F}, "HALT", 0);
		}

		void addInst(ISANode *r, const std::vector<uint8_t> &opcode, const std::string &mnemo, int immSize)
		{
			ISANode *current = r;

			for(size_t i = 0; i < opcode.size(); i++)
			{
				uint8_t byte = opcode[i];

				if(current->children.find(byte) == current->children.end())
				{
					current->children[byte] = new ISANode();
					current->children[byte]->opcode = std::vector<uint8_t>(opcode.begin(), opcode.begin() + i + 1);
				}

				current = current->children[byte];
			}

			current->is_term = true;
			current->mnemo = mnemo;
			current->immSize = immSize;
		}

		std::string nomz_mnemo(const std::string &line)
		{
			std::string res;
			bool in_space = false;

			for(char c : line)
			{
				if(std::isspace(c))
				{
					if(!in_space && !res.empty())
					{
						res += ' ';
						in_space = true;
					}
				}
				else if(c == ',')
				{
					if(!res.empty() && res.back() == ' ') res.pop_back();
					res += ',';
					in_space = false;
				}
				else
				{
					res += std::toupper(c);
					in_space = false;
				}
			}

			for(size_t i = 0; i < res.size(); i++)
			{
				if(res[i] == ',' && i + 1 < res.size() && res[i + 1] != ' ') res.insert(i + 1, " ");
			}

			return res;
		}

		bool findInst(const std::string &mnemo, std::vector<uint8_t> &outOp, int &outImmSize)
		{
			std::string norm = nomz_mnemo(mnemo);
			return searchTree(isaR, norm, outOp, outImmSize);
		}

		bool searchTree(ISANode *node, const std::string &tgt, std::vector<uint8_t> &outOp, int &outImmSize)
		{
			if(node->is_term && node->mnemo == tgt)
			{
				outOp = node->opcode;
				outImmSize = node->immSize;
				return true;
			}

			for(auto &pair : node->children)
			{
				if(searchTree(pair.second, tgt, outOp, outImmSize)) return true;
			}

			return false;
		}

		bool parceImm(const std::string &str, uint32_t &val)
		{
			try
			{
				if(str.substr(0, 2) == "0x") val = std::stoul(str.substr(2), nullptr, 16);
				else if(str.substr(0, 2) == "0o") val = std::stoul(str.substr(2), nullptr, 8);
				else if(str.substr(0, 2) == "0s") val = std::stoul(str.substr(2), nullptr, 6);
				else if(str.substr(0, 2) == "0b") val = std::stoul(str.substr(2), nullptr, 2);
				else val = std::stoul(str.substr(2));

				return true;
			}
			catch(...) {return false;}
		}

		void appendImm(uint32_t val, int bytes)
		{
			for(int i = 0; i < bytes; i++) binary.push_back((val >> (i * 8)) & 0xFF);
		}

	public:
		XASM(): origin(0), isaR(nullptr)
		{
			buildTree();
		}

		~XASM()
		{
			delete isaR;
		}

		bool l_asmbl(const std::string &line)
		{
			if(line.empty() || line[0] == ';') return true;

			std::string trimmed = line;
			size_t commPos = trimmed.find(';');
			if(commPos != std::string::npos) trimmed = trimmed.substr(0, commPos);

			if(trimmed.empty()) return true;

			std::istringstream iss(trimmed);
			std::string fword;
			iss >> fword;

			if(fword == "ORG")
			{
				std::string addrStr;
				iss >> addrStr;
				parceImm(addrStr, origin);
				return true;
			}

			std::string mnemoWImm = trimmed;
			uint32_t immV = 0;
			bool hasImm = false;

			size_t lastSpace = trimmed.rfind(' ');
			if(lastSpace != std::string::npos)
			{
				std::string lastToken = trimmed.substr(lastSpace + 1);

				if(!lastToken.empty() && (std::isdigit(lastToken[0]) || (2 < lastToken.size() && lastToken[0] == '0' && (lastToken[1] == 'x' || lastToken[1] == 'o' || lastToken[1] == 's' || lastToken[1] == 'd' || lastToken[1] || 'b'))))
				{
					if(parceImm(lastToken, immV))
					{
						hasImm = true;
						mnemoWImm = trimmed.substr(0, lastSpace) + " IMM";
					}
				}
			}

			std::vector<uint8_t> opcode;
			int immSize;

			if(findInst(mnemoWImm, opcode, immSize))
			{
				for(uint8_t byte : opcode) binary.push_back(byte);

				if(hasImm && 0 < immSize)
				{
					appendImm(immV, immSize);
				}

				return true;
			}

			std::cerr << "[ ERROR ] XASM: l_asmbl: Unknown instruction: " << trimmed << std::endl;
			return false;
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

		bool w2f(const std::string &fname)
		{
			std::ofstream file(fname, std::ios::binary);
			if(!file)
			{
				std::cerr << "[ERROR ] XASM: w2f: Cannnot open file: " << fname << std::endl;
				return false;
			}

			file.write(reinterpret_cast<const char*>(binary.data()), binary.size());

			return true;
		}
};

////////////////////////////////////////////////////////

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

	if(ifname.empty())
	{
		std::cerr << "[ERROR] XASM: No input file specified" << std::endl;
		return 1;
	}

	if(ofname.empty()) ofname = "a.bin";

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