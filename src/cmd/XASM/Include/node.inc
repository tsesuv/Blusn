#ifndef US_NODE
#define US_NODE

#include "xasm.inc"

struct Node
{
	std::string mnemo; // "LD EAX, EBX" のような完全なニーモニック
	std::vector<uint8_t> opcode; // このノードまでのオペコード列
	std::map<uint8_t, Node*> children; // 次のバイト値 -> 子ノード
	bool is_term; // 命令の終端か
	int immSize; // 即値のバイト数（0なら即値なし）

	Node(): is_term(false), immSize(0) {}

	~Node()
	{
		for(auto &pair : children)
		{
			delete pair.second;
		}
	}
};

#endif /* node.inc */
