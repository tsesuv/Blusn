#ifndef US_ASMBL
#define US_ASMBL

#include "xasm.inc"
#include "node.inc"
#include "util.inc"
#include "build.inc"

class XASM
{
	private:
		std::vector<uint8_t> binary;
		uint32_t origin = 0;
		Node *r;

		bool findInst(const std::string &mnemo, std::vector<uint8_t> &outOp, int &outImmSize)
		{
			std::string norm = nomz_mnemo(mnemo);
			return searchTree(r, norm, outOp, outImmSize);
		}

		bool searchTree(Node *node, const std::string &tgt, std::vector<uint8_t> &outOp, int &outImmSize)
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
				else val = std::stoul(str, nullptr, 10);

				return true;
			}
			catch(...) {return false;}
		}

		void appendImm(uint32_t val, int bytes)
		{
			for(int i = 0; i < bytes; i++) binary.push_back((val >> (i * 8)) & 0xFF);
		}

	public:
		XASM(): origin(0), r(nullptr)
		{
			r = new Node();
			buildTree(r);
		}

		~XASM()
		{
			delete r;
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
				std::string immToken = lastToken;
				bool brkImm = false;

				// support [IMM] form (e.g., LD EAX, [0x2000])
				if(!lastToken.empty() && lastToken.front() == '[' && lastToken.back() == ']')
				{
					immToken = lastToken.substr(1, lastToken.size() - 2);
					brkImm = true;
				}

				if(!immToken.empty() && (std::isdigit(immToken[0]) || (2 < immToken.size() && immToken[0] == '0' && (immToken[1] == 'x' || immToken[1] == 'o' || immToken[1] == 's' || immToken[1] == 'd' || immToken[1] == 'b'))))
				{
					if(parceImm(immToken, immV))
					{
						hasImm = true;
						if(brkImm) mnemoWImm = trimmed.substr(0, lastSpace) + " [IMM]";
						else mnemoWImm = trimmed.substr(0, lastSpace) + " IMM";
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
				std::cerr << "[ ERROR ] XASM: w2f: Cannnot open file: " << fname << std::endl;
				return false;
			}

			file.write(reinterpret_cast<const char*>(binary.data()), binary.size());

			return true;
		}
};

#endif /* asmbl.inc */
