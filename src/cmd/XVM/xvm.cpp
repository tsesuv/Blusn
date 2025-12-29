/* UnSynk XMC Virtual Machine */
/* Version: 1.0.0 Pre-Alpha */
/* Created by UnSynk, tsesuv nostel */

#include "xvm.inc"
#include "cpu.inc"
#include "exec.inc"
#include "inst.inc"
#include "mem.inc"

////////////////////////////////////////////////////////

int main(int ac, char **av)
{
	MEM mem;
	Inst inst;
	std::vector<uint8_t> bytes;
	InstInfo info;
	Exec exe;
	CPU cpu;

	mem.init(1024);
	cpu.initMem(&mem);
	cpu.reset();
	inst.initTable(&mem);
	exe.init(&cpu, &mem, &inst);

	mem.writeByte(0, 0x00);

	mem.writeByte(1, 0x01);
	mem.writeByte(2, 0x00);
	mem.writeByte(3, 0x00);
	mem.writeByte(4, 0x0F);
	mem.writeDouble(5, 0x01010000);
	mem.writeDouble(9, 0x34120000);

	if(inst.decode(0, bytes, 10, &info)) printf("Decoded: len = %d, hasImm = %d\n", info.len, info.hasImm);

	int al = 0;
	while(cpu.getPC() < 14)
	{
		bytes.clear();
		inst.decode(cpu.getPC(), bytes, 4, &info);
		exe.run(0, info);
		std::cout << "PC is " << cpu.getPC() << " now" << std::endl;
		std::cout << "EAX: " << *cpu.getReg(0) << std::endl;
		std::cout << "Now circle: " << al + 1 << std::endl;
		al++;
		if(5 < al)
		{
			cpu.setIRQ(cpu.IRQ_TIMER);
		}
	}

	mem.free();

	return 0;
}
