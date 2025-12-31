#ifndef US_CORE
#define US_CORE

#include "xvm.inc"
#include "cpu.inc"
#include "mem.inc"
#include "inst.inc"
#include "exec.inc"

////////////////////////////////////////////////////////

class Core
{
	private:
		MEM mem;
		CPU cpu;
		Inst inst;
		InstInfo info;
		Exec exec;
		std::vector<uint8_t> bytes;

		bool init(uint32_t memSize)
		{
			mem.init(memSize);
			cpu.initMem(&mem);
			cpu.reset();
			inst.initTable(&mem);
			exec.init(&cpu, &mem, &inst);

			return true;
		}

	public:
		bool exeVM(void)
		{
			return true;
		}

}

#endif
