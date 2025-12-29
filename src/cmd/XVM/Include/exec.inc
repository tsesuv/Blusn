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

		uint32_t readImm(uint32_t addr, uint8_t len)
		{
			uint32_t v = 0;
			uint32_t weight = 1;
			for(size_t i = 0; i < len; i++)
			{
				uint8_t tmp;
				mem->readByte(addr + i, &tmp);
				v += tmp * weight;
				weight *= 0x100;
			}
			return v;
		}

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
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
				cpu->setReg(0, *cpu->getReg(0) + v);
			}
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x00, 0x01}, 4)) cpu->setReg(0, *cpu->getReg(0) + *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x00, 0x02}, 4)) cpu->setReg(0, *cpu->getReg(0) + *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x00, 0x03}, 4)) cpu->setReg(0, *cpu->getReg(0) + *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x00, 0x04}, 4)) cpu->setReg(0, *cpu->getReg(0) + *cpu->getReg(4));

			// ADD EBX, ...
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
				cpu->setReg(1, *cpu->getReg(1) + v);
			}
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x01}, 4)) cpu->setReg(1, *cpu->getReg(1) + *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x02}, 4)) cpu->setReg(1, *cpu->getReg(1) + *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x03}, 4)) cpu->setReg(1, *cpu->getReg(1) + *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x04}, 4)) cpu->setReg(1, *cpu->getReg(1) + *cpu->getReg(4));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x05}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
				cpu->setReg(8, *cpu->getReg(8) + v);
			}
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x06}, 4)) cpu->setReg(8, *cpu->getReg(8) + *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x07}, 4)) cpu->setReg(8, *cpu->getReg(8) + *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x08}, 4)) cpu->setReg(8, *cpu->getReg(8) + *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x09}, 4)) cpu->setReg(8, *cpu->getReg(8) + *cpu->getReg(4));

			// ADD ECX, ...
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x02, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
				cpu->setReg(2, *cpu->getReg(2) + v);
			}
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x02, 0x01}, 4)) cpu->setReg(2, *cpu->getReg(2) + *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x02, 0x02}, 4)) cpu->setReg(2, *cpu->getReg(2) + *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x02, 0x03}, 4)) cpu->setReg(2, *cpu->getReg(2) + *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x02, 0x04}, 4)) cpu->setReg(2, *cpu->getReg(2) + *cpu->getReg(4));

			// ADD EDX, ...
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x03, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
				cpu->setReg(3, *cpu->getReg(3) + v);
			}
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x03, 0x01}, 4)) cpu->setReg(3, *cpu->getReg(3) + *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x03, 0x02}, 4)) cpu->setReg(3, *cpu->getReg(3) + *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x03, 0x03}, 4)) cpu->setReg(3, *cpu->getReg(3) + *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x03, 0x04}, 4)) cpu->setReg(3, *cpu->getReg(3) + *cpu->getReg(4));

			// ADD EEX, ...
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x04, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
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

			// SUB系
			// SUB EAX, ...
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x00, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
				cpu->setReg(0, *cpu->getReg(0) - v);
			}
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x00, 0x01}, 4)) cpu->setReg(0, *cpu->getReg(0) - *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x00, 0x02}, 4)) cpu->setReg(0, *cpu->getReg(0) - *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x00, 0x03}, 4)) cpu->setReg(0, *cpu->getReg(0) - *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x00, 0x04}, 4)) cpu->setReg(0, *cpu->getReg(0) - *cpu->getReg(4));

			// SUB EBX, ...
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x01, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
				cpu->setReg(1, *cpu->getReg(1) - v);
			}
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x01, 0x01}, 4)) cpu->setReg(1, *cpu->getReg(1) - *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x01, 0x02}, 4)) cpu->setReg(1, *cpu->getReg(1) - *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x01, 0x03}, 4)) cpu->setReg(1, *cpu->getReg(1) - *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x01, 0x04}, 4)) cpu->setReg(1, *cpu->getReg(1) - *cpu->getReg(4));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x01, 0x05}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
				cpu->setReg(8, *cpu->getReg(8) - v);
			}
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x01, 0x06}, 4)) cpu->setReg(8, *cpu->getReg(8) - *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x01, 0x07}, 4)) cpu->setReg(8, *cpu->getReg(8) - *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x01, 0x08}, 4)) cpu->setReg(8, *cpu->getReg(8) - *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x01, 0x09}, 4)) cpu->setReg(8, *cpu->getReg(8) - *cpu->getReg(4));

			// SUB ECX, ...
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x02, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
				cpu->setReg(2, *cpu->getReg(2) - v);
			}
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x02, 0x01}, 4)) cpu->setReg(2, *cpu->getReg(2) - *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x02, 0x02}, 4)) cpu->setReg(2, *cpu->getReg(2) - *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x02, 0x03}, 4)) cpu->setReg(2, *cpu->getReg(2) - *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x02, 0x04}, 4)) cpu->setReg(2, *cpu->getReg(2) - *cpu->getReg(4));

			// SUB EDX, ...
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x03, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
				cpu->setReg(3, *cpu->getReg(3) - v);
			}
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x03, 0x01}, 4)) cpu->setReg(3, *cpu->getReg(3) - *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x03, 0x02}, 4)) cpu->setReg(3, *cpu->getReg(3) - *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x03, 0x03}, 4)) cpu->setReg(3, *cpu->getReg(3) - *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x03, 0x04}, 4)) cpu->setReg(3, *cpu->getReg(3) - *cpu->getReg(4));

			// SUB EEX, ...
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x04, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
				cpu->setReg(4, *cpu->getReg(4) - v);
			}
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x04, 0x01}, 4)) cpu->setReg(4, *cpu->getReg(4) - *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x04, 0x02}, 4)) cpu->setReg(4, *cpu->getReg(4) - *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x04, 0x03}, 4)) cpu->setReg(4, *cpu->getReg(4) - *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x04, 0x04}, 4)) cpu->setReg(4, *cpu->getReg(4) - *cpu->getReg(3));

			// LD系
			// LD EAX, ...
			else if(inst->chkInst(info.oplist, {0x03, 0x00, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
				cpu->setReg(0, v);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x00, 0x01}, 3)) cpu->setReg(0, *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x03, 0x00, 0x02}, 3)) cpu->setReg(0, *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x03, 0x00, 0x03}, 3)) cpu->setReg(0, *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x03, 0x00, 0x04}, 3)) cpu->setReg(0, *cpu->getReg(4));
			else if(inst->chkInst(info.oplist, {0x03, 0x00, 0x05}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
				uint32_t w = 0;
				mem->readDouble(v, &w);
				cpu->setReg(0, w);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x00, 0x06}, 3)) cpu->setReg(0, *cpu->getReg(9));
			else if(inst->chkInst(info.oplist, {0x03, 0x00, 0x07}, 3)) cpu->setReg(0, *cpu->getReg(10));
			else if(inst->chkInst(info.oplist, {0x03, 0x00, 0x08}, 3)) cpu->setReg(0, *cpu->getReg(11));
			else if(inst->chkInst(info.oplist, {0x03, 0x00, 0x09}, 3)) cpu->setReg(0, *cpu->getReg(12));
			else if(inst->chkInst(info.oplist, {0x03, 0x00, 0x0A}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
				mem->writeDouble(*cpu->getReg(0), v);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x00, 0x0B}, 3)) mem->writeDouble(*cpu->getReg(0), *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x03, 0x00, 0x0C}, 3)) mem->writeDouble(*cpu->getReg(0), *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x03, 0x00, 0x0D}, 3)) mem->writeDouble(*cpu->getReg(0), *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x03, 0x00, 0x0E}, 3)) mem->writeDouble(*cpu->getReg(0), *cpu->getReg(4));
			else if(inst->chkInst(info.oplist, {0x03, 0x00, 0x0F}, 3)) mem->writeDouble(*cpu->getReg(0), *cpu->getReg(5));
			else if(inst->chkInst(info.oplist, {0x03, 0x00, 0x10}, 3)) mem->writeDouble(*cpu->getReg(0), *cpu->getReg(6));

			// LD EBX, ...
			else if(inst->chkInst(info.oplist, {0x03, 0x01, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
				mem->writeDouble(*cpu->getReg(1), v);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x01, 0x01}, 3)) cpu->setReg(1, *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x03, 0x01, 0x02}, 3)) cpu->setReg(1, *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x03, 0x01, 0x03}, 3)) cpu->setReg(1, *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x03, 0x01, 0x04}, 3)) cpu->setReg(1, *cpu->getReg(4));
			else if(inst->chkInst(info.oplist, {0x03, 0x01, 0x05}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
				uint32_t w = 0;
				mem->readDouble(v, &w);
				cpu->setReg(1, w);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x01, 0x06}, 3)) cpu->setReg(1, *cpu->getReg(9));
			else if(inst->chkInst(info.oplist, {0x03, 0x01, 0x07}, 3)) cpu->setReg(1, *cpu->getReg(10));
			else if(inst->chkInst(info.oplist, {0x03, 0x01, 0x08}, 3)) cpu->setReg(1, *cpu->getReg(11));
			else if(inst->chkInst(info.oplist, {0x03, 0x01, 0x09}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
				mem->writeDouble(*cpu->getReg(1), v);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x01, 0x0A}, 3)) cpu->setReg(8, *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x03, 0x01, 0x0B}, 3)) cpu->setReg(8, *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x03, 0x01, 0x0C}, 3)) cpu->setReg(8, *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x03, 0x01, 0x0D}, 3)) cpu->setReg(8, *cpu->getReg(4));
			else if(inst->chkInst(info.oplist, {0x03, 0x01, 0x0E}, 3)) cpu->setReg(8, *cpu->getReg(5));
			else if(inst->chkInst(info.oplist, {0x03, 0x01, 0x0F}, 3)) cpu->setReg(8, *cpu->getReg(6));
			else if(inst->chkInst(info.oplist, {0x03, 0x01, 0x10}, 3)) cpu->setReg(8, *cpu->getReg(7));

			// LD ECX, ...
			else if(inst->chkInst(info.oplist, {0x03, 0x02, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
				mem->writeDouble(*cpu->getReg(2), v);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x02, 0x01}, 3)) cpu->setReg(2, *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x03, 0x02, 0x02}, 3)) cpu->setReg(2, *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x03, 0x02, 0x03}, 3)) cpu->setReg(2, *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x03, 0x02, 0x04}, 3)) cpu->setReg(2, *cpu->getReg(4));

			// LD EDX, ...
			else if(inst->chkInst(info.oplist, {0x03, 0x03, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
				mem->writeDouble(*cpu->getReg(3), v);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x03, 0x01}, 3)) cpu->setReg(3, *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x03, 0x03, 0x02}, 3)) cpu->setReg(3, *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x03, 0x03, 0x03}, 3)) cpu->setReg(3, *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x03, 0x03, 0x04}, 3)) cpu->setReg(3, *cpu->getReg(4));

			// LD EEX, ...
			else if(inst->chkInst(info.oplist, {0x03, 0x04, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
				mem->writeDouble(*cpu->getReg(4), v);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x04, 0x01}, 3)) cpu->setReg(4, *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x03, 0x04, 0x02}, 3)) cpu->setReg(4, *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x03, 0x04, 0x03}, 3)) cpu->setReg(4, *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x03, 0x04, 0x04}, 3)) cpu->setReg(4, *cpu->getReg(3));

			// LD EDI, ...
			else if(inst->chkInst(info.oplist, {0x03, 0x05, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
				mem->writeDouble(*cpu->getReg(5), v);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x05, 0x01}, 3)) cpu->setReg(5, *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x03, 0x05, 0x02}, 3)) cpu->setReg(5, *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x03, 0x05, 0x03}, 3)) cpu->setReg(5, *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x03, 0x05, 0x04}, 3)) cpu->setReg(5, *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x03, 0x05, 0x05}, 3)) cpu->setReg(5, *cpu->getReg(4));
			else if(inst->chkInst(info.oplist, {0x03, 0x05, 0x06}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
				uint32_t w = 0;
				mem->readDouble(v, &w);
				cpu->setReg(5, w);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x05, 0x07}, 3)) cpu->setReg(5, *cpu->getReg(8));
			else if(inst->chkInst(info.oplist, {0x03, 0x05, 0x08}, 3)) cpu->setReg(5, *cpu->getReg(9));
			else if(inst->chkInst(info.oplist, {0x03, 0x05, 0x09}, 3)) cpu->setReg(5, *cpu->getReg(10));
			else if(inst->chkInst(info.oplist, {0x03, 0x05, 0x0A}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
				cpu->setReg(9, v);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x05, 0x0B}, 3)) cpu->setReg(9, *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x03, 0x05, 0x0C}, 3)) cpu->setReg(9, *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x03, 0x05, 0x0D}, 3)) cpu->setReg(9, *cpu->getReg(6));

			// LD ESI, ...
			else if(inst->chkInst(info.oplist, {0x03, 0x06, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
				mem->writeDouble(*cpu->getReg(6), v);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x06, 0x01}, 3)) cpu->setReg(6, *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x03, 0x06, 0x02}, 3)) cpu->setReg(6, *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x03, 0x06, 0x03}, 3)) cpu->setReg(6, *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x03, 0x06, 0x04}, 3)) cpu->setReg(6, *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x03, 0x06, 0x05}, 3)) cpu->setReg(6, *cpu->getReg(4));
			else if(inst->chkInst(info.oplist, {0x03, 0x06, 0x06}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
				uint32_t w = 0;
				mem->readDouble(v, &w);
				cpu->setReg(6, w);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x06, 0x07}, 3)) cpu->setReg(6, *cpu->getReg(8));
			else if(inst->chkInst(info.oplist, {0x03, 0x06, 0x08}, 3)) cpu->setReg(6, *cpu->getReg(9));
			else if(inst->chkInst(info.oplist, {0x03, 0x06, 0x09}, 3)) cpu->setReg(6, *cpu->getReg(10));
			else if(inst->chkInst(info.oplist, {0x03, 0x06, 0x0A}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
				cpu->setReg(10, v);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x06, 0x0B}, 3)) cpu->setReg(10, *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x03, 0x06, 0x0C}, 3)) cpu->setReg(10, *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x03, 0x06, 0x0D}, 3)) cpu->setReg(10, *cpu->getReg(5));

			// LD EBP, ...
			else if(inst->chkInst(info.oplist, {0x03, 0x07, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
				mem->writeDouble(*cpu->getReg(7), v);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x07, 0x01}, 3)) cpu->setReg(7, *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x03, 0x07, 0x02}, 3)) cpu->setReg(7, *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x03, 0x07, 0x03}, 3)) cpu->setReg(7, *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x03, 0x07, 0x04}, 3)) cpu->setReg(7, *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x03, 0x07, 0x05}, 3)) cpu->setReg(7, *cpu->getReg(4));
			else if(inst->chkInst(info.oplist, {0x03, 0x07, 0x06}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
				uint32_t w = 0;
				mem->readDouble(v, &w);
				cpu->setReg(7, w);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x07, 0x07}, 3)) cpu->setReg(7, *cpu->getReg(8));
			else if(inst->chkInst(info.oplist, {0x03, 0x07, 0x08}, 3)) cpu->setReg(7, *cpu->getReg(9));
			else if(inst->chkInst(info.oplist, {0x03, 0x07, 0x09}, 3)) cpu->setReg(7, *cpu->getReg(10));
			else if(inst->chkInst(info.oplist, {0x03, 0x07, 0x0A}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.immLen + 1, info.immLen);
				cpu->setReg(11, v);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x07, 0x0B}, 3)) cpu->setReg(11, *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x03, 0x07, 0x0C}, 3)) cpu->setReg(11, *cpu->getReg(3));

			// HALT
			else if(inst->chkInst(info.oplist, {0x0F}, 1)) if(cpu->chkIRQ(~0) == 0) return false;
			else return false;

			cpu->setPC(cpu->getPC() + info.len);
			if(info.hasImm) cpu->setPC(cpu->getPC() + info.immLen);

			return true;
		}
};

#endif
