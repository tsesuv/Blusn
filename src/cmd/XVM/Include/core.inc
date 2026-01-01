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

	public:
		bool power = true;

			bool init(uint32_t memSize)
			{
				mem.init(memSize);
				cpu.initMem(&mem);
				cpu.reset();
				inst.initTable(&mem);
				exec.init(&cpu, &mem, &inst);

				return true;
			}

		bool exeVM(uint32_t memSize)
		{
			if(power)
			{
				if(timer)
				{
					if(!inst.decode(cpu.getPC(), bytes, 4, &info)) return false;
					if(!exec.run(cpu.getPC(), info)) return false;

					if(cpu.getIRQ(cpu.FLAG_R))
					{
						cpu.clrIRQ(cpu.FLAG_R);
						init(memSize);
					}
				}
			}

			return true;
		}

}

#endif
