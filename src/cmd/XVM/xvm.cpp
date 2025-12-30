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

	mem.writeByte(5, 0x03);
	mem.writeByte(6, 0x01);
	mem.writeByte(7, 0x00);
	mem.writeDouble(8, 0x01000000);

	mem.writeDouble(12, 0x00000000);

	mem.writeDouble(16, 0x02010105);
	mem.writeDouble(20, 0x01000000);

	mem.writeDouble(24, 0x00000000);

	if(inst.decode(0, bytes, 10, &info)) printf("Decoded: len = %d, hasImm = %d\n", info.len, info.hasImm);

	int al = 0;
	while(cpu.getPC() < 30)
	{
		bytes.clear();
		inst.decode(cpu.getPC(), bytes, 4, &info);
		exe.run(0, info);
		printf("Decoded: len = %d, hasImm = %d\n", info.len, info.hasImm);
		for(int i = 0; i < bytes.size(); i++) std::cout << std::hex << (int)bytes[i] << std::dec << " ";
		std::cout << std::endl;
		std::cout << "PC is " << std::hex << cpu.getPC() << std::dec << " now" << std::endl;
		std::cout << "EAX: " << std::hex << *cpu.getReg(0) << std::dec << std::endl;
		std::cout << "EBX: " << std::hex << *cpu.getReg(1) << std::dec << std::endl;

		if(al % 2 == 0) cpu.setIRQ(cpu.IRQ_TIMER);
		else cpu.clrIRQ(cpu.IRQ_TIMER);
		al++;
	}

	mem.free();

	return 0;
}
