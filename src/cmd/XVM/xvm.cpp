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
	mem.writeByte(4, 0x00);
	mem.writeByte(5, 0x03);
	mem.writeByte(6, 0x01);
	mem.writeByte(7, 0x00);
	mem.writeDouble(8, 0x34120000);
	mem.writeDouble(12, 0x00000000);
	mem.writeDouble(16, 0x02010105);
	mem.writeDouble(20, 0x34000000);

	if(inst.decode(0, bytes, 10, &info)) printf("Decoded: len = %d, hasImm = %d\n", info.len, info.hasImm);

	int al = 0;
	while(cpu.getPC() < 20)
	{
		bytes.clear();
		inst.decode(cpu.getPC(), bytes, 4, &info);
		exe.run(0, info);
		printf("Decoded: len = %d, hasImm = %d\n", info.len, info.hasImm);
		std::cout << "PC is " << cpu.getPC() << " now" << std::endl;
		std::cout << "EAX: " << *cpu.getReg(0) << std::endl;
		std::cout << "EBX: " << *cpu.getReg(1) << std::endl;
	}

	mem.free();

	return 0;
}
