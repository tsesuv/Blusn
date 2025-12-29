#ifndef US_EXEC
#define US_EXEC

#include "xvm.inc"
#include "cpu.inc"
#include "inst.inc"
#include "mem.inc"

class Exec
{
	private:
		CPU *cpu;
		MEM *mem;
		Inst *inst;

	public:
		bool init(CPU *cpuP, MEM *memP, Inst *instP)
		{
			cpu = cpuP;
			mem = memP;
			inst = instP;

			return true;
		}

		bool run(uint32_t addr, InstInfo info)
		{
			// NOP
			if(inst->chkInst(info.oplist, {0x00}, 1));

			// INC系
			else if(inst->chkInst(info.oplist, {0x01, 0x00, 0x00}, 3)) cpu->setReg(0, *cpu->getReg(0) + 1);
			else if(inst->chkInst(info.oplist, {0x01, 0x00, 0x01}, 3)) cpu->setReg(1, *cpu->getReg(1) + 1);
			else if(inst->chkInst(info.oplist, {0x01, 0x00, 0x02}, 3))
			{
				uint8_t tmp;
				mem->readByte(*cpu->getReg(8), &tmp);
				mem->writeByte(*cpu->getReg(8), tmp + 1);
			}
			else if(inst->chkInst(info.oplist, {0x01, 0x00, 0x03}, 3)) cpu->setReg(2, *cpu->getReg(2) + 1);
			else if(inst->chkInst(info.oplist, {0x01, 0x00, 0x04}, 3)) cpu->setReg(3, *cpu->getReg(3) + 1);
			else if(inst->chkInst(info.oplist, {0x01, 0x00, 0x05}, 3)) cpu->setReg(4, *cpu->getReg(4) + 1);
			else if(inst->chkInst(info.oplist, {0x01, 0x00, 0x06}, 3)) cpu->setReg(5, *cpu->getReg(5) + 1);

			// ADD系
			// ADD EAX, ...
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x00, 0x00}, 4))
			{
				uint8_t tmp;
				uint32_t v = 0;
				uint32_t ewight = 1;
				for(size_t i = 0; i < info.immLen; i++)
				{
					mem->readByte(cpu->getPC() + info.immLen + i + 1, &tmp);
					v += tmp * ewight;
					ewight *= 0x100;
				}
				cpu->setReg(0, *cpu->getReg(0) + v);
			}
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x00, 0x01}, 4)) cpu->setReg(0, *cpu->getReg(0) + *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x00, 0x02}, 4)) cpu->setReg(0, *cpu->getReg(0) + *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x00, 0x03}, 4)) cpu->setReg(0, *cpu->getReg(0) + *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x00, 0x04}, 4)) cpu->setReg(0, *cpu->getReg(0) + *cpu->getReg(4));

			// ADD EBX, ...
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x00}, 4))
			{
				uint8_t tmp;
				uint32_t v = 0;
				uint32_t ewight = 1;
				for(size_t i = 0; i < info.immLen; i++)
				{
					mem->readByte(cpu->getPC() + info.immLen + i + 1, &tmp);
					v += tmp * ewight;
					ewight *= 0x100;
				}
				cpu->setReg(1, *cpu->getReg(1) + v);
			}
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x01}, 4)) cpu->setReg(1, *cpu->getReg(1) + *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x02}, 4)) cpu->setReg(1, *cpu->getReg(1) + *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x03}, 4)) cpu->setReg(1, *cpu->getReg(1) + *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x04}, 4)) cpu->setReg(1, *cpu->getReg(1) + *cpu->getReg(4));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x05}, 4))
			{
				uint8_t tmp;
				uint32_t v = 0;
				uint32_t ewight = 1;
				for(size_t i = 0; i < info.immLen; i++)
				{
					mem->readByte(cpu->getPC() + info.immLen + i + 1, &tmp);
					v += tmp * ewight;
					ewight *= 0x100;
				}
				cpu->setReg(8, *cpu->getReg(8) + v);
			}
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x06}, 4)) cpu->setReg(8, *cpu->getReg(8) + *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x07}, 4)) cpu->setReg(8, *cpu->getReg(8) + *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x08}, 4)) cpu->setReg(8, *cpu->getReg(8) + *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x09}, 4)) cpu->setReg(8, *cpu->getReg(8) + *cpu->getReg(4));

			// ADD ECX, ...
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x02, 0x00}, 4))
			{
				uint8_t tmp;
				uint32_t v = 0;
				uint32_t ewight = 1;
				for(size_t i = 0; i < info.immLen; i++)
				{
					mem->readByte(cpu->getPC() + info.immLen + i + 1, &tmp);
					v += tmp * ewight;
					ewight *= 0x100;
				}
				cpu->setReg(2, *cpu->getReg(2) + v);
			}
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x02, 0x01}, 4)) cpu->setReg(2, *cpu->getReg(2) + *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x02, 0x02}, 4)) cpu->setReg(2, *cpu->getReg(2) + *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x02, 0x03}, 4)) cpu->setReg(2, *cpu->getReg(2) + *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x02, 0x04}, 4)) cpu->setReg(2, *cpu->getReg(2) + *cpu->getReg(4));

			// ADD EDX, ...
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x03, 0x00}, 4))
			{
				uint8_t tmp;
				uint32_t v = 0;
				uint32_t ewight = 1;
				for(size_t i = 0; i < info.immLen; i++)
				{
					mem->readByte(cpu->getPC() + info.immLen + i + 1, &tmp);
					v += tmp * ewight;
					ewight *= 0x100;
				}
				cpu->setReg(3, *cpu->getReg(3) + v);
			}
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x03, 0x01}, 4)) cpu->setReg(3, *cpu->getReg(3) + *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x03, 0x02}, 4)) cpu->setReg(3, *cpu->getReg(3) + *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x03, 0x03}, 4)) cpu->setReg(3, *cpu->getReg(3) + *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x03, 0x04}, 4)) cpu->setReg(3, *cpu->getReg(3) + *cpu->getReg(4));

			// ADD EEX, ...
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x04, 0x00}, 4))
			{
				uint8_t tmp;
				uint32_t v = 0;
				uint32_t ewight = 1;
				for(size_t i = 0; i < info.immLen; i++)
				{
					mem->readByte(cpu->getPC() + info.immLen + i + 1, &tmp);
					v += tmp * ewight;
					ewight *= 0x100;
				}
				cpu->setReg(4, *cpu->getReg(4) + v);
			}
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x04, 0x01}, 4)) cpu->setReg(4, *cpu->getReg(4) + *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x04, 0x02}, 4)) cpu->setReg(4, *cpu->getReg(4) + *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x04, 0x03}, 4)) cpu->setReg(4, *cpu->getReg(4) + *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x04, 0x04}, 4)) cpu->setReg(4, *cpu->getReg(4) + *cpu->getReg(3));

			// DEC系
			else if(inst->chkInst(info.oplist, {0x02, 0x00, 0x00}, 3)) cpu->setReg(0, *cpu->getReg(0) - 1);
			else if(inst->chkInst(info.oplist, {0x02, 0x00, 0x01}, 3)) cpu->setReg(1, *cpu->getReg(1) - 1);
			else if(inst->chkInst(info.oplist, {0x02, 0x00, 0x02}, 3))
			{
				uint8_t tmp;
				mem->readByte(*cpu->getReg(8), &tmp);
				mem->writeByte(*cpu->getReg(8), tmp - 1);
			}
			else if(inst->chkInst(info.oplist, {0x02, 0x00, 0x03}, 3)) cpu->setReg(2, *cpu->getReg(2) - 1);
			else if(inst->chkInst(info.oplist, {0x02, 0x00, 0x04}, 3)) cpu->setReg(3, *cpu->getReg(3) - 1);
			else if(inst->chkInst(info.oplist, {0x02, 0x00, 0x05}, 3)) cpu->setReg(4, *cpu->getReg(4) - 1);
			else if(inst->chkInst(info.oplist, {0x02, 0x00, 0x06}, 3)) cpu->setReg(5, *cpu->getReg(5) - 1);

			// HALT
			else if(inst->chkInst(info.oplist, {0x0F}, 1)) if(cpu->chkIRQ(~0) == 0) return false;
			else return false;

			cpu->setPC(cpu->getPC() + info.len);
			if(info.hasImm) cpu->setPC(cpu->getPC() + info.immLen);

			return true;
		}
};

#endif
