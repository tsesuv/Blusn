#ifndef US_BUILD
#define US_BUILD

#include "node.inc"

inline bool addInst(Node *r, const std::vector<uint8_t> &opcode, const std::string &mnemo, int immSize)
{
	Node *current = r;

	for(size_t i = 0; i < opcode.size(); i++)
	{
		uint8_t byte = opcode[i];

		if(current->children.find(byte) == current->children.end())
		{
			current->children[byte] = new Node();
			current->children[byte]->opcode = std::vector<uint8_t>(opcode.begin(), opcode.begin() + i + 1);
		}

		current = current->children[byte];
	}

	current->is_term = true;
	current->mnemo = mnemo;
	current->immSize = immSize;

	return true;
}

inline bool buildTree(Node *r)
{
	r = new Node();

	// NOP
	addInst(r, {0x00}, "NOP", 0);

	// INC系
	addInst(r, {0x01, 0x00, 0x00}, "INC EAX", 0);
	addInst(r, {0x01, 0x00, 0x01}, "INC EBX", 0);
	addInst(r, {0x01, 0x00, 0x02}, "INC [EBX]", 0);
	addInst(r, {0x01, 0x00, 0x03}, "INC ECX", 0);
	addInst(r, {0x01, 0x00, 0x04}, "INC EDX", 0);
	addInst(r, {0x01, 0x00, 0x05}, "INC EEX", 0);
	addInst(r, {0x01, 0x00, 0x06}, "INC EDI", 0);

	// ADD系
	// ADD EAX, ...
	addInst(r, {0x01, 0x01, 0x00, 0x00}, "ADD EAX, IMM", 4);
	addInst(r, {0x01, 0x01, 0x00, 0x01}, "ADD EAX, EBX", 0);
	addInst(r, {0x01, 0x01, 0x00, 0x02}, "ADD EAX, ECX", 0);
	addInst(r, {0x01, 0x01, 0x00, 0x03}, "ADD EAX, EDX", 0);
	addInst(r, {0x01, 0x01, 0x00, 0x04}, "ADD EAX, EEX", 0);

	// ADD EBX, ...
	addInst(r, {0x01, 0x01, 0x01, 0x00}, "ADD EBX, IMM", 4);
	addInst(r, {0x01, 0x01, 0x01, 0x01}, "ADD EBX, EAX", 0);
	addInst(r, {0x01, 0x01, 0x01, 0x02}, "ADD EBX, ECX", 0);
	addInst(r, {0x01, 0x01, 0x01, 0x03}, "ADD EBX, EDX", 0);
	addInst(r, {0x01, 0x01, 0x01, 0x04}, "ADD EBX, EEX", 0);
	addInst(r, {0x01, 0x01, 0x01, 0x05}, "ADD [EBX], IMM", 4);
	addInst(r, {0x01, 0x01, 0x01, 0x06}, "ADD [EBX], EAX", 0);
	addInst(r, {0x01, 0x01, 0x01, 0x07}, "ADD [EBX], ECX", 0);
	addInst(r, {0x01, 0x01, 0x01, 0x08}, "ADD [EBX], EDX", 0);
	addInst(r, {0x01, 0x01, 0x01, 0x09}, "ADD [EBX], EEX", 0);

	// LD系
	// LD EAX, ...
	addInst(r, {0x03, 0x00, 0x00}, "LD EAX, IMM", 4);
	addInst(r, {0x03, 0x00, 0x01}, "LD EAX, EBX", 0);
	addInst(r, {0x03, 0x00, 0x02}, "LD EAX, ECX", 0);
	addInst(r, {0x03, 0x00, 0x03}, "LD EAX, EDX", 0);
	addInst(r, {0x03, 0x00, 0x04}, "LD EAX, EEX", 0);
	addInst(r, {0x03, 0x00, 0x05}, "LD EAX, [IMM]", 4);
	addInst(r, {0x03, 0x00, 0x06}, "LD EAX, [EBX]", 0);
	addInst(r, {0x03, 0x00, 0x07}, "LD EAX, [EDI]", 0);
	addInst(r, {0x03, 0x00, 0x08}, "LD EAX, [ESI]", 0);
	addInst(r, {0x03, 0x00, 0x09}, "LD EAX, [EBP]", 0);
	addInst(r, {0x03, 0x00, 0x0A}, "LD [EAX], IMM", 4);
	addInst(r, {0x03, 0x00, 0x0B}, "LD [EAX], EBX", 0);
	addInst(r, {0x03, 0x00, 0x0C}, "LD [EAX], ECX", 0);
	addInst(r, {0x03, 0x00, 0x0D}, "LD [EAX], EDX", 0);
	addInst(r, {0x03, 0x00, 0x0E}, "LD [EAX], EEX", 0);
	addInst(r, {0x03, 0x00, 0x0F}, "LD [EAX], EDI", 0);
	addInst(r, {0x03, 0x00, 0x10}, "LD [EAX], EBP", 0);

	// LD EBX, ...
	addInst(r, {0x03, 0x01, 0x00}, "LD EBX, IMM", 4);
	addInst(r, {0x03, 0x01, 0x01}, "LD EBX, EAX", 0);
	addInst(r, {0x03, 0x01, 0x02}, "LD EBX, ECX", 0);
	addInst(r, {0x03, 0x01, 0x03}, "LD EBX, EDX", 0);
	addInst(r, {0x03, 0x01, 0x04}, "LD EBX, EEX", 0);
	addInst(r, {0x03, 0x01, 0x05}, "LD EBX, [IMM]", 4);
	addInst(r, {0x03, 0x01, 0x06}, "LD EBX, [EDI]", 0);
	addInst(r, {0x03, 0x01, 0x07}, "LD EBX, [ESI]", 0);
	addInst(r, {0x03, 0x01, 0x08}, "LD EBX, [EBP]", 0);
	addInst(r, {0x03, 0x01, 0x09}, "LD [EBX], IMM", 4);
	addInst(r, {0x03, 0x01, 0x0A}, "LD [EBX], EAX", 0);
	addInst(r, {0x03, 0x01, 0x0B}, "LD [EBX], ECX", 0);
	addInst(r, {0x03, 0x01, 0x0C}, "LD [EBX], EDX", 0);
	addInst(r, {0x03, 0x01, 0x0D}, "LD [EBX], EEX", 0);
	addInst(r, {0x03, 0x01, 0x0E}, "LD [EBX], EDI", 0);
	addInst(r, {0x03, 0x01, 0x0F}, "LD [EBX], ESI", 0);
	addInst(r, {0x03, 0x01, 0x10}, "LD [EBX], EBP", 0);

	// LD ECX, ...
	addInst(r, {0x03, 0x02, 0x00}, "LD ECX, IMM", 4);
	addInst(r, {0x03, 0x02, 0x01}, "LD ECX, EAX", 0);
	addInst(r, {0x03, 0x02, 0x02}, "LD ECX, EBX", 0);
	addInst(r, {0x03, 0x02, 0x03}, "LD ECX, EDX", 0);
	addInst(r, {0x03, 0x02, 0x04}, "LD ECX, EEX", 0);

	// LD EDX, ...
	addInst(r, {0x03, 0x03, 0x00}, "LD EDX, IMM", 4);
	addInst(r, {0x03, 0x03, 0x01}, "LD EDX, EAX", 0);
	addInst(r, {0x03, 0x03, 0x02}, "LD EDX, EBX", 0);
	addInst(r, {0x03, 0x03, 0x03}, "LD EDX, ECX", 0);
	addInst(r, {0x03, 0x03, 0x04}, "LD EDX, EEX", 0);

	// LD EEX, ...
	addInst(r, {0x03, 0x04, 0x00}, "LD EEX, IMM", 4);
	addInst(r, {0x03, 0x04, 0x01}, "LD EEX, EAX", 0);
	addInst(r, {0x03, 0x04, 0x02}, "LD EEX, EBX", 0);
	addInst(r, {0x03, 0x04, 0x03}, "LD EEX, ECX", 0);
	addInst(r, {0x03, 0x04, 0x04}, "LD EEX, EDX", 0);

	// CALL系
	addInst(r, {0x0C, 0x00}, "CALL EAX", 0);
	addInst(r, {0x0C, 0x01}, "CALL EBX", 0);
	addInst(r, {0x0C, 0x02}, "CALL ECX", 0);
	addInst(r, {0x0C, 0x03}, "CALL EDX", 0);
	addInst(r, {0x0C, 0x04}, "CALL EEX", 0);

	// RET, HALT
	addInst(r, {0x0E}, "RET", 0);
	addInst(r, {0x0F}, "HALT", 0);

	return true;
}

#endif
