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
			uint8_t tmp = 0;
			uint32_t v = 0;
			uint32_t weight = 1;
			for(size_t i = 0; i < len; i++)
			{
				mem->readByte(addr + i, &tmp);
				v += tmp * weight;
				weight *= 0x100;
			}
			return v;
		}

		bool push(int regID)
		{
			mem->writeDouble(cpu->getSP(), *cpu->getReg(regID));
			cpu->pushSP(4);

			return true;
		}

		bool pop(int regID)
		{
			uint32_t v;
			cpu->popSP(4);
			mem->readDouble(cpu->getSP(), &v);
			cpu->setReg(regID, v);

			return true;
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
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(0, *cpu->getReg(0) + v);
			}
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x00, 0x01}, 4)) cpu->setReg(0, *cpu->getReg(0) + *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x00, 0x02}, 4)) cpu->setReg(0, *cpu->getReg(0) + *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x00, 0x03}, 4)) cpu->setReg(0, *cpu->getReg(0) + *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x00, 0x04}, 4)) cpu->setReg(0, *cpu->getReg(0) + *cpu->getReg(4));

			// ADD EBX, ...
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(1, *cpu->getReg(1) + v);
			}
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x01}, 4)) cpu->setReg(1, *cpu->getReg(1) + *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x02}, 4)) cpu->setReg(1, *cpu->getReg(1) + *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x03}, 4)) cpu->setReg(1, *cpu->getReg(1) + *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x04}, 4)) cpu->setReg(1, *cpu->getReg(1) + *cpu->getReg(4));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x05}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(8, *cpu->getReg(8) + v);
			}
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x06}, 4)) cpu->setReg(8, *cpu->getReg(8) + *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x07}, 4)) cpu->setReg(8, *cpu->getReg(8) + *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x08}, 4)) cpu->setReg(8, *cpu->getReg(8) + *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x01, 0x09}, 4)) cpu->setReg(8, *cpu->getReg(8) + *cpu->getReg(4));

			// ADD ECX, ...
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x02, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(2, *cpu->getReg(2) + v);
			}
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x02, 0x01}, 4)) cpu->setReg(2, *cpu->getReg(2) + *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x02, 0x02}, 4)) cpu->setReg(2, *cpu->getReg(2) + *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x02, 0x03}, 4)) cpu->setReg(2, *cpu->getReg(2) + *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x02, 0x04}, 4)) cpu->setReg(2, *cpu->getReg(2) + *cpu->getReg(4));

			// ADD EDX, ...
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x03, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(3, *cpu->getReg(3) + v);
			}
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x03, 0x01}, 4)) cpu->setReg(3, *cpu->getReg(3) + *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x03, 0x02}, 4)) cpu->setReg(3, *cpu->getReg(3) + *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x03, 0x03}, 4)) cpu->setReg(3, *cpu->getReg(3) + *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x03, 0x04}, 4)) cpu->setReg(3, *cpu->getReg(3) + *cpu->getReg(4));

			// ADD EEX, ...
			else if(inst->chkInst(info.oplist, {0x01, 0x01, 0x04, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
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
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(0, *cpu->getReg(0) - v);
			}
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x00, 0x01}, 4)) cpu->setReg(0, *cpu->getReg(0) - *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x00, 0x02}, 4)) cpu->setReg(0, *cpu->getReg(0) - *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x00, 0x03}, 4)) cpu->setReg(0, *cpu->getReg(0) - *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x00, 0x04}, 4)) cpu->setReg(0, *cpu->getReg(0) - *cpu->getReg(4));

			// SUB EBX, ...
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x01, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(1, *cpu->getReg(1) - v);
			}
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x01, 0x01}, 4)) cpu->setReg(1, *cpu->getReg(1) - *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x01, 0x02}, 4)) cpu->setReg(1, *cpu->getReg(1) - *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x01, 0x03}, 4)) cpu->setReg(1, *cpu->getReg(1) - *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x01, 0x04}, 4)) cpu->setReg(1, *cpu->getReg(1) - *cpu->getReg(4));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x01, 0x05}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(8, *cpu->getReg(8) - v);
			}
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x01, 0x06}, 4)) cpu->setReg(8, *cpu->getReg(8) - *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x01, 0x07}, 4)) cpu->setReg(8, *cpu->getReg(8) - *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x01, 0x08}, 4)) cpu->setReg(8, *cpu->getReg(8) - *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x01, 0x09}, 4)) cpu->setReg(8, *cpu->getReg(8) - *cpu->getReg(4));

			// SUB ECX, ...
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x02, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(2, *cpu->getReg(2) - v);
			}
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x02, 0x01}, 4)) cpu->setReg(2, *cpu->getReg(2) - *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x02, 0x02}, 4)) cpu->setReg(2, *cpu->getReg(2) - *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x02, 0x03}, 4)) cpu->setReg(2, *cpu->getReg(2) - *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x02, 0x04}, 4)) cpu->setReg(2, *cpu->getReg(2) - *cpu->getReg(4));

			// SUB EDX, ...
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x03, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(3, *cpu->getReg(3) - v);
			}
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x03, 0x01}, 4)) cpu->setReg(3, *cpu->getReg(3) - *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x03, 0x02}, 4)) cpu->setReg(3, *cpu->getReg(3) - *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x03, 0x03}, 4)) cpu->setReg(3, *cpu->getReg(3) - *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x03, 0x04}, 4)) cpu->setReg(3, *cpu->getReg(3) - *cpu->getReg(4));

			// SUB EEX, ...
			else if(inst->chkInst(info.oplist, {0x02, 0x01, 0x04, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
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
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(0, v);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x00, 0x01}, 3)) cpu->setReg(0, *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x03, 0x00, 0x02}, 3)) cpu->setReg(0, *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x03, 0x00, 0x03}, 3)) cpu->setReg(0, *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x03, 0x00, 0x04}, 3)) cpu->setReg(0, *cpu->getReg(4));
			else if(inst->chkInst(info.oplist, {0x03, 0x00, 0x05}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
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
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
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
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(1, v);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x01, 0x01}, 3)) cpu->setReg(1, *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x03, 0x01, 0x02}, 3)) cpu->setReg(1, *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x03, 0x01, 0x03}, 3)) cpu->setReg(1, *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x03, 0x01, 0x04}, 3)) cpu->setReg(1, *cpu->getReg(4));
			else if(inst->chkInst(info.oplist, {0x03, 0x01, 0x05}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				uint32_t w = 0;
				mem->readDouble(v, &w);
				cpu->setReg(1, w);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x01, 0x06}, 3)) cpu->setReg(1, *cpu->getReg(9));
			else if(inst->chkInst(info.oplist, {0x03, 0x01, 0x07}, 3)) cpu->setReg(1, *cpu->getReg(10));
			else if(inst->chkInst(info.oplist, {0x03, 0x01, 0x08}, 3)) cpu->setReg(1, *cpu->getReg(11));
			else if(inst->chkInst(info.oplist, {0x03, 0x01, 0x09}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
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
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				mem->writeDouble(*cpu->getReg(2), v);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x02, 0x01}, 3)) cpu->setReg(2, *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x03, 0x02, 0x02}, 3)) cpu->setReg(2, *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x03, 0x02, 0x03}, 3)) cpu->setReg(2, *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x03, 0x02, 0x04}, 3)) cpu->setReg(2, *cpu->getReg(4));

			// LD EDX, ...
			else if(inst->chkInst(info.oplist, {0x03, 0x03, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				mem->writeDouble(*cpu->getReg(3), v);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x03, 0x01}, 3)) cpu->setReg(3, *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x03, 0x03, 0x02}, 3)) cpu->setReg(3, *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x03, 0x03, 0x03}, 3)) cpu->setReg(3, *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x03, 0x03, 0x04}, 3)) cpu->setReg(3, *cpu->getReg(4));

			// LD EEX, ...
			else if(inst->chkInst(info.oplist, {0x03, 0x04, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				mem->writeDouble(*cpu->getReg(4), v);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x04, 0x01}, 3)) cpu->setReg(4, *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x03, 0x04, 0x02}, 3)) cpu->setReg(4, *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x03, 0x04, 0x03}, 3)) cpu->setReg(4, *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x03, 0x04, 0x04}, 3)) cpu->setReg(4, *cpu->getReg(3));

			// LD EDI, ...
			else if(inst->chkInst(info.oplist, {0x03, 0x05, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				mem->writeDouble(*cpu->getReg(5), v);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x05, 0x01}, 3)) cpu->setReg(5, *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x03, 0x05, 0x02}, 3)) cpu->setReg(5, *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x03, 0x05, 0x03}, 3)) cpu->setReg(5, *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x03, 0x05, 0x04}, 3)) cpu->setReg(5, *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x03, 0x05, 0x05}, 3)) cpu->setReg(5, *cpu->getReg(4));
			else if(inst->chkInst(info.oplist, {0x03, 0x05, 0x06}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				uint32_t w = 0;
				mem->readDouble(v, &w);
				cpu->setReg(5, w);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x05, 0x07}, 3)) cpu->setReg(5, *cpu->getReg(8));
			else if(inst->chkInst(info.oplist, {0x03, 0x05, 0x08}, 3)) cpu->setReg(5, *cpu->getReg(9));
			else if(inst->chkInst(info.oplist, {0x03, 0x05, 0x09}, 3)) cpu->setReg(5, *cpu->getReg(10));
			else if(inst->chkInst(info.oplist, {0x03, 0x05, 0x0A}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(9, v);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x05, 0x0B}, 3)) cpu->setReg(9, *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x03, 0x05, 0x0C}, 3)) cpu->setReg(9, *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x03, 0x05, 0x0D}, 3)) cpu->setReg(9, *cpu->getReg(6));

			// LD ESI, ...
			else if(inst->chkInst(info.oplist, {0x03, 0x06, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				mem->writeDouble(*cpu->getReg(6), v);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x06, 0x01}, 3)) cpu->setReg(6, *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x03, 0x06, 0x02}, 3)) cpu->setReg(6, *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x03, 0x06, 0x03}, 3)) cpu->setReg(6, *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x03, 0x06, 0x04}, 3)) cpu->setReg(6, *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x03, 0x06, 0x05}, 3)) cpu->setReg(6, *cpu->getReg(4));
			else if(inst->chkInst(info.oplist, {0x03, 0x06, 0x06}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				uint32_t w = 0;
				mem->readDouble(v, &w);
				cpu->setReg(6, w);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x06, 0x07}, 3)) cpu->setReg(6, *cpu->getReg(8));
			else if(inst->chkInst(info.oplist, {0x03, 0x06, 0x08}, 3)) cpu->setReg(6, *cpu->getReg(9));
			else if(inst->chkInst(info.oplist, {0x03, 0x06, 0x09}, 3)) cpu->setReg(6, *cpu->getReg(10));
			else if(inst->chkInst(info.oplist, {0x03, 0x06, 0x0A}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(10, v);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x06, 0x0B}, 3)) cpu->setReg(10, *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x03, 0x06, 0x0C}, 3)) cpu->setReg(10, *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x03, 0x06, 0x0D}, 3)) cpu->setReg(10, *cpu->getReg(5));

			// LD EBP, ...
			else if(inst->chkInst(info.oplist, {0x03, 0x07, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				mem->writeDouble(*cpu->getReg(7), v);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x07, 0x01}, 3)) cpu->setReg(7, *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x03, 0x07, 0x02}, 3)) cpu->setReg(7, *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x03, 0x07, 0x03}, 3)) cpu->setReg(7, *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x03, 0x07, 0x04}, 3)) cpu->setReg(7, *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x03, 0x07, 0x05}, 3)) cpu->setReg(7, *cpu->getReg(4));
			else if(inst->chkInst(info.oplist, {0x03, 0x07, 0x06}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				uint32_t w = 0;
				mem->readDouble(v, &w);
				cpu->setReg(7, w);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x07, 0x07}, 3)) cpu->setReg(7, *cpu->getReg(8));
			else if(inst->chkInst(info.oplist, {0x03, 0x07, 0x08}, 3)) cpu->setReg(7, *cpu->getReg(9));
			else if(inst->chkInst(info.oplist, {0x03, 0x07, 0x09}, 3)) cpu->setReg(7, *cpu->getReg(10));
			else if(inst->chkInst(info.oplist, {0x03, 0x07, 0x0A}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(11, v);
			}
			else if(inst->chkInst(info.oplist, {0x03, 0x07, 0x0B}, 3)) cpu->setReg(11, *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x03, 0x07, 0x0C}, 3)) cpu->setReg(11, *cpu->getReg(3));

			// OR系
			// OR EAX, ...
			else if(inst->chkInst(info.oplist, {0x04, 0x00, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				uint32_t w = 0;
				mem->readDouble(v, &w);
				cpu->setReg(0, *cpu->getReg(0) | w);
			}
			else if(inst->chkInst(info.oplist, {0x04, 0x00, 0x01}, 3)) cpu->setReg(0, *cpu->getReg(0) | *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x04, 0x00, 0x02}, 3)) cpu->setReg(0, *cpu->getReg(0) | *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x04, 0x00, 0x03}, 3)) cpu->setReg(0, *cpu->getReg(0) | *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x04, 0x00, 0x04}, 3)) cpu->setReg(0, *cpu->getReg(0) | *cpu->getReg(4));

			// OR EBX, ...
			else if(inst->chkInst(info.oplist, {0x04, 0x01, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				uint32_t w = 0;
				mem->readDouble(v, &w);
				cpu->setReg(1, *cpu->getReg(1) | w);
			}
			else if(inst->chkInst(info.oplist, {0x04, 0x01, 0x01}, 3)) cpu->setReg(1, *cpu->getReg(1) | *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x04, 0x01, 0x02}, 3)) cpu->setReg(1, *cpu->getReg(1) | *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x04, 0x01, 0x03}, 3)) cpu->setReg(1, *cpu->getReg(1) | *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x04, 0x01, 0x04}, 3)) cpu->setReg(1, *cpu->getReg(1) | *cpu->getReg(4));

			// OR ECX, ...
			else if(inst->chkInst(info.oplist, {0x04, 0x02, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				uint32_t w = 0;
				mem->readDouble(v, &w);
				cpu->setReg(2, *cpu->getReg(2) | w);
			}
			else if(inst->chkInst(info.oplist, {0x04, 0x02, 0x01}, 3)) cpu->setReg(2, *cpu->getReg(2) | *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x04, 0x02, 0x02}, 3)) cpu->setReg(2, *cpu->getReg(2) | *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x04, 0x02, 0x03}, 3)) cpu->setReg(2, *cpu->getReg(2) | *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x04, 0x02, 0x04}, 3)) cpu->setReg(2, *cpu->getReg(2) | *cpu->getReg(4));

			// OR EDX, ...
			else if(inst->chkInst(info.oplist, {0x04, 0x03, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				uint32_t w = 0;
				mem->readDouble(v, &w);
				cpu->setReg(3, *cpu->getReg(3) | w);
			}
			else if(inst->chkInst(info.oplist, {0x04, 0x03, 0x01}, 3)) cpu->setReg(3, *cpu->getReg(3) | *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x04, 0x03, 0x02}, 3)) cpu->setReg(3, *cpu->getReg(3) | *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x04, 0x03, 0x03}, 3)) cpu->setReg(3, *cpu->getReg(3) | *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x04, 0x03, 0x04}, 3)) cpu->setReg(3, *cpu->getReg(3) | *cpu->getReg(4));

			// OR EEX, ...
			else if(inst->chkInst(info.oplist, {0x04, 0x04, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				uint32_t w = 0;
				mem->readDouble(v, &w);
				cpu->setReg(4, *cpu->getReg(4) | w);
			}
			else if(inst->chkInst(info.oplist, {0x04, 0x04, 0x01}, 3)) cpu->setReg(4, *cpu->getReg(4) | *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x04, 0x04, 0x02}, 3)) cpu->setReg(4, *cpu->getReg(4) | *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x04, 0x04, 0x03}, 3)) cpu->setReg(4, *cpu->getReg(4) | *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x04, 0x04, 0x04}, 3)) cpu->setReg(4, *cpu->getReg(4) | *cpu->getReg(3));

			// AND系
			// AND EAX, ...
			else if(inst->chkInst(info.oplist, {0x05, 0x00, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				uint32_t w = 0;
				mem->readDouble(v, &w);
				cpu->setReg(0, *cpu->getReg(0) & w);
			}
			else if(inst->chkInst(info.oplist, {0x05, 0x00, 0x01}, 3)) cpu->setReg(0, *cpu->getReg(0) & *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x05, 0x00, 0x02}, 3)) cpu->setReg(0, *cpu->getReg(0) & *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x05, 0x00, 0x03}, 3)) cpu->setReg(0, *cpu->getReg(0) & *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x05, 0x00, 0x04}, 3)) cpu->setReg(0, *cpu->getReg(0) & *cpu->getReg(4));

			// AND EBX, ...
			else if(inst->chkInst(info.oplist, {0x05, 0x01, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				uint32_t w = 0;
				mem->readDouble(v, &w);
				cpu->setReg(1, *cpu->getReg(1) & w);
			}
			else if(inst->chkInst(info.oplist, {0x05, 0x01, 0x01}, 3)) cpu->setReg(1, *cpu->getReg(1) & *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x05, 0x01, 0x02}, 3)) cpu->setReg(1, *cpu->getReg(1) & *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x05, 0x01, 0x03}, 3)) cpu->setReg(1, *cpu->getReg(1) & *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x05, 0x01, 0x04}, 3)) cpu->setReg(1, *cpu->getReg(1) & *cpu->getReg(4));

			// AND ECX, ...
			else if(inst->chkInst(info.oplist, {0x05, 0x02, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				uint32_t w = 0;
				mem->readDouble(v, &w);
				cpu->setReg(2, *cpu->getReg(2) & w);
			}
			else if(inst->chkInst(info.oplist, {0x05, 0x02, 0x01}, 3)) cpu->setReg(2, *cpu->getReg(2) & *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x05, 0x02, 0x02}, 3)) cpu->setReg(2, *cpu->getReg(2) & *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x05, 0x02, 0x03}, 3)) cpu->setReg(2, *cpu->getReg(2) & *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x05, 0x02, 0x04}, 3)) cpu->setReg(2, *cpu->getReg(2) & *cpu->getReg(4));

			// AND EDX, ...
			else if(inst->chkInst(info.oplist, {0x05, 0x03, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				uint32_t w = 0;
				mem->readDouble(v, &w);
				cpu->setReg(3, *cpu->getReg(3) & w);
			}
			else if(inst->chkInst(info.oplist, {0x05, 0x03, 0x01}, 3)) cpu->setReg(3, *cpu->getReg(3) & *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x05, 0x03, 0x02}, 3)) cpu->setReg(3, *cpu->getReg(3) & *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x05, 0x03, 0x03}, 3)) cpu->setReg(3, *cpu->getReg(3) & *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x05, 0x03, 0x04}, 3)) cpu->setReg(3, *cpu->getReg(3) & *cpu->getReg(4));

			// AND EEX, ...
			else if(inst->chkInst(info.oplist, {0x05, 0x04, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				uint32_t w = 0;
				mem->readDouble(v, &w);
				cpu->setReg(4, *cpu->getReg(4) & w);
			}
			else if(inst->chkInst(info.oplist, {0x05, 0x04, 0x01}, 3)) cpu->setReg(4, *cpu->getReg(4) & *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x05, 0x04, 0x02}, 3)) cpu->setReg(4, *cpu->getReg(4) & *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x05, 0x04, 0x03}, 3)) cpu->setReg(4, *cpu->getReg(4) & *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x05, 0x04, 0x04}, 3)) cpu->setReg(4, *cpu->getReg(4) & *cpu->getReg(3));

			// XOR系
			// XOR EAX, ...
			else if(inst->chkInst(info.oplist, {0x06, 0x00, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				uint32_t w = 0;
				mem->readDouble(v, &w);
				cpu->setReg(0, *cpu->getReg(0) ^ w);
			}
			else if(inst->chkInst(info.oplist, {0x06, 0x00, 0x01}, 3)) cpu->setReg(0, *cpu->getReg(0) ^ *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x06, 0x00, 0x02}, 3)) cpu->setReg(0, *cpu->getReg(0) ^ *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x06, 0x00, 0x03}, 3)) cpu->setReg(0, *cpu->getReg(0) ^ *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x06, 0x00, 0x04}, 3)) cpu->setReg(0, *cpu->getReg(0) ^ *cpu->getReg(4));

			// XOR EBX, ...
			else if(inst->chkInst(info.oplist, {0x06, 0x01, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				uint32_t w = 0;
				mem->readDouble(v, &w);
				cpu->setReg(1, *cpu->getReg(1) ^ w);
			}
			else if(inst->chkInst(info.oplist, {0x06, 0x01, 0x01}, 3)) cpu->setReg(1, *cpu->getReg(1) ^ *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x06, 0x01, 0x02}, 3)) cpu->setReg(1, *cpu->getReg(1) ^ *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x06, 0x01, 0x03}, 3)) cpu->setReg(1, *cpu->getReg(1) ^ *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x06, 0x01, 0x04}, 3)) cpu->setReg(1, *cpu->getReg(1) ^ *cpu->getReg(4));

			// XOR ECX, ...
			else if(inst->chkInst(info.oplist, {0x06, 0x02, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				uint32_t w = 0;
				mem->readDouble(v, &w);
				cpu->setReg(2, *cpu->getReg(2) ^ w);
			}
			else if(inst->chkInst(info.oplist, {0x06, 0x02, 0x01}, 3)) cpu->setReg(2, *cpu->getReg(2) ^ *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x06, 0x02, 0x02}, 3)) cpu->setReg(2, *cpu->getReg(2) ^ *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x06, 0x02, 0x03}, 3)) cpu->setReg(2, *cpu->getReg(2) ^ *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x06, 0x02, 0x04}, 3)) cpu->setReg(2, *cpu->getReg(2) ^ *cpu->getReg(4));

			// XOR EDX, ...
			else if(inst->chkInst(info.oplist, {0x06, 0x03, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				uint32_t w = 0;
				mem->readDouble(v, &w);
				cpu->setReg(3, *cpu->getReg(3) ^ w);
			}
			else if(inst->chkInst(info.oplist, {0x06, 0x03, 0x01}, 3)) cpu->setReg(3, *cpu->getReg(3) ^ *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x06, 0x03, 0x02}, 3)) cpu->setReg(3, *cpu->getReg(3) ^ *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x06, 0x03, 0x03}, 3)) cpu->setReg(3, *cpu->getReg(3) ^ *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x06, 0x03, 0x04}, 3)) cpu->setReg(3, *cpu->getReg(3) ^ *cpu->getReg(4));

			// XOR EEX, ...
			else if(inst->chkInst(info.oplist, {0x06, 0x04, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				uint32_t w = 0;
				mem->readDouble(v, &w);
				cpu->setReg(4, *cpu->getReg(4) ^ w);
			}
			else if(inst->chkInst(info.oplist, {0x06, 0x04, 0x01}, 3)) cpu->setReg(4, *cpu->getReg(4) ^ *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x06, 0x04, 0x02}, 3)) cpu->setReg(4, *cpu->getReg(4) ^ *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x06, 0x04, 0x03}, 3)) cpu->setReg(4, *cpu->getReg(4) ^ *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x06, 0x04, 0x04}, 3)) cpu->setReg(4, *cpu->getReg(4) ^ *cpu->getReg(3));

			// NOT系
			else if(inst->chkInst(info.oplist, {0x07, 0x00, 0x00}, 3)) cpu->setReg(0, ~*cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x07, 0x00, 0x01}, 3)) cpu->setReg(1, ~*cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x07, 0x00, 0x02}, 3)) cpu->setReg(2, ~*cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x07, 0x00, 0x03}, 3)) cpu->setReg(3, ~*cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x07, 0x00, 0x04}, 3)) cpu->setReg(4, ~*cpu->getReg(4));

			// LST系
			// LST EAX, ...
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x00, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(0, *cpu->getReg(0) << v);
			}
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x00, 0x01}, 4)) cpu->setReg(0, *cpu->getReg(0) << *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x00, 0x02}, 4)) cpu->setReg(0, *cpu->getReg(0) << *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x00, 0x03}, 4)) cpu->setReg(0, *cpu->getReg(0) << *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x00, 0x04}, 4)) cpu->setReg(0, *cpu->getReg(0) << *cpu->getReg(4));

			// LST EBX, ...
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x01, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(1, *cpu->getReg(1) << v);
			}
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x01, 0x01}, 4)) cpu->setReg(1, *cpu->getReg(1) << *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x01, 0x02}, 4)) cpu->setReg(1, *cpu->getReg(1) << *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x01, 0x03}, 4)) cpu->setReg(1, *cpu->getReg(1) << *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x01, 0x04}, 4)) cpu->setReg(1, *cpu->getReg(1) << *cpu->getReg(4));
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x01, 0x05}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(8, *cpu->getReg(8) << v);
			}
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x01, 0x06}, 4)) cpu->setReg(8, *cpu->getReg(8) << *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x01, 0x07}, 4)) cpu->setReg(8, *cpu->getReg(8) << *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x01, 0x08}, 4)) cpu->setReg(8, *cpu->getReg(8) << *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x01, 0x09}, 4)) cpu->setReg(8, *cpu->getReg(8) << *cpu->getReg(4));

			// LST ECX, ...
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x02, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(2, *cpu->getReg(2) << v);
			}
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x02, 0x01}, 4)) cpu->setReg(2, *cpu->getReg(2) << *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x02, 0x02}, 4)) cpu->setReg(2, *cpu->getReg(2) << *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x02, 0x03}, 4)) cpu->setReg(2, *cpu->getReg(2) << *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x02, 0x04}, 4)) cpu->setReg(2, *cpu->getReg(2) << *cpu->getReg(4));

			// LST EDX, ...
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x03, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(3, *cpu->getReg(3) << v);
			}
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x03, 0x01}, 4)) cpu->setReg(3, *cpu->getReg(3) << *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x03, 0x02}, 4)) cpu->setReg(3, *cpu->getReg(3) << *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x03, 0x03}, 4)) cpu->setReg(3, *cpu->getReg(3) << *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x03, 0x04}, 4)) cpu->setReg(3, *cpu->getReg(3) << *cpu->getReg(4));

			// LST EEX, ...
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x04, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(4, *cpu->getReg(4) << v);
			}
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x04, 0x01}, 4)) cpu->setReg(4, *cpu->getReg(4) << *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x04, 0x02}, 4)) cpu->setReg(4, *cpu->getReg(4) << *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x04, 0x03}, 4)) cpu->setReg(4, *cpu->getReg(4) << *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x08, 0x00, 0x04, 0x04}, 4)) cpu->setReg(4, *cpu->getReg(4) << *cpu->getReg(3));

			// RST系
			// RST EAX, ...
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x00, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(0, *cpu->getReg(0) >> v);
			}
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x00, 0x01}, 4)) cpu->setReg(0, *cpu->getReg(0) >> *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x00, 0x02}, 4)) cpu->setReg(0, *cpu->getReg(0) >> *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x00, 0x03}, 4)) cpu->setReg(0, *cpu->getReg(0) >> *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x00, 0x04}, 4)) cpu->setReg(0, *cpu->getReg(0) >> *cpu->getReg(4));

			// RST EBX, ...
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x01, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(1, *cpu->getReg(1) >> v);
			}
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x01, 0x01}, 4)) cpu->setReg(1, *cpu->getReg(1) >> *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x01, 0x02}, 4)) cpu->setReg(1, *cpu->getReg(1) >> *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x01, 0x03}, 4)) cpu->setReg(1, *cpu->getReg(1) >> *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x01, 0x04}, 4)) cpu->setReg(1, *cpu->getReg(1) >> *cpu->getReg(4));
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x01, 0x05}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(8, *cpu->getReg(8) >> v);
			}
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x01, 0x06}, 4)) cpu->setReg(8, *cpu->getReg(8) >> *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x01, 0x07}, 4)) cpu->setReg(8, *cpu->getReg(8) >> *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x01, 0x08}, 4)) cpu->setReg(8, *cpu->getReg(8) >> *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x01, 0x09}, 4)) cpu->setReg(8, *cpu->getReg(8) >> *cpu->getReg(4));

			// RST ECX, ...
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x02, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(2, *cpu->getReg(2) >> v);
			}
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x02, 0x01}, 4)) cpu->setReg(2, *cpu->getReg(2) >> *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x02, 0x02}, 4)) cpu->setReg(2, *cpu->getReg(2) >> *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x02, 0x03}, 4)) cpu->setReg(2, *cpu->getReg(2) >> *cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x02, 0x04}, 4)) cpu->setReg(2, *cpu->getReg(2) >> *cpu->getReg(4));

			// RST EDX, ...
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x03, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(3, *cpu->getReg(3) >> v);
			}
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x03, 0x01}, 4)) cpu->setReg(3, *cpu->getReg(3) >> *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x03, 0x02}, 4)) cpu->setReg(3, *cpu->getReg(3) >> *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x03, 0x03}, 4)) cpu->setReg(3, *cpu->getReg(3) >> *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x03, 0x04}, 4)) cpu->setReg(3, *cpu->getReg(3) >> *cpu->getReg(4));

			// RST EEX, ...
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x04, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(4, *cpu->getReg(4) >> v);
			}
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x04, 0x01}, 4)) cpu->setReg(4, *cpu->getReg(4) >> *cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x04, 0x02}, 4)) cpu->setReg(4, *cpu->getReg(4) >> *cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x04, 0x03}, 4)) cpu->setReg(4, *cpu->getReg(4) >> *cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x08, 0x01, 0x04, 0x04}, 4)) cpu->setReg(4, *cpu->getReg(4) >> *cpu->getReg(3));

			// LLT系
			// LLT EAX, ...
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x00, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(0, *cpu->getReg(0) << v + *cpu->getReg(0) >> (32 - v));
			}
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x00, 0x01}, 4)) cpu->setReg(0, *cpu->getReg(0) << *cpu->getReg(1) + *cpu->getReg(0) >> (32 - *cpu->getReg(1)));
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x00, 0x02}, 4)) cpu->setReg(0, *cpu->getReg(0) << *cpu->getReg(2) + *cpu->getReg(0) >> (32 - *cpu->getReg(2)));
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x00, 0x03}, 4)) cpu->setReg(0, *cpu->getReg(0) << *cpu->getReg(3) + *cpu->getReg(0) >> (32 - *cpu->getReg(3)));
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x00, 0x04}, 4)) cpu->setReg(0, *cpu->getReg(0) << *cpu->getReg(4) + *cpu->getReg(0) >> (32 - *cpu->getReg(4)));

			// LLT EBX, ...
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x01, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(1, *cpu->getReg(1) << v + *cpu->getReg(1) >> (32 - v));
			}
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x01, 0x01}, 4)) cpu->setReg(1, *cpu->getReg(1) << *cpu->getReg(0) + *cpu->getReg(1) >> (32 - *cpu->getReg(0)));
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x01, 0x02}, 4)) cpu->setReg(1, *cpu->getReg(1) << *cpu->getReg(2) + *cpu->getReg(1) >> (32 - *cpu->getReg(2)));
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x01, 0x03}, 4)) cpu->setReg(1, *cpu->getReg(1) << *cpu->getReg(3) + *cpu->getReg(1) >> (32 - *cpu->getReg(3)));
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x01, 0x04}, 4)) cpu->setReg(1, *cpu->getReg(1) << *cpu->getReg(4) + *cpu->getReg(1) >> (32 - *cpu->getReg(4)));
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x01, 0x05}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(8, *cpu->getReg(8) << v + *cpu->getReg(8) >> (32 - v));
			}
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x01, 0x06}, 4)) cpu->setReg(8, *cpu->getReg(8) << *cpu->getReg(0) + *cpu->getReg(8) >> (32 - *cpu->getReg(0)));
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x01, 0x07}, 4)) cpu->setReg(8, *cpu->getReg(8) << *cpu->getReg(2) + *cpu->getReg(8) >> (32 - *cpu->getReg(2)));
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x01, 0x08}, 4)) cpu->setReg(8, *cpu->getReg(8) << *cpu->getReg(3) + *cpu->getReg(8) >> (32 - *cpu->getReg(3)));
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x01, 0x09}, 4)) cpu->setReg(8, *cpu->getReg(8) << *cpu->getReg(4) + *cpu->getReg(8) >> (32 - *cpu->getReg(4)));

			// LLT ECX, ...
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x02, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(2, *cpu->getReg(2) << v + *cpu->getReg(2) >> (32 - v));
			}
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x02, 0x01}, 4)) cpu->setReg(2, *cpu->getReg(2) << *cpu->getReg(0) + *cpu->getReg(2) >> (32 - *cpu->getReg(0)));
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x02, 0x02}, 4)) cpu->setReg(2, *cpu->getReg(2) << *cpu->getReg(1) + *cpu->getReg(2) >> (32 - *cpu->getReg(1)));
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x02, 0x03}, 4)) cpu->setReg(2, *cpu->getReg(2) << *cpu->getReg(3) + *cpu->getReg(2) >> (32 - *cpu->getReg(3)));
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x02, 0x04}, 4)) cpu->setReg(2, *cpu->getReg(2) << *cpu->getReg(4) + *cpu->getReg(2) >> (32 - *cpu->getReg(4)));

			// LLT EDX, ...
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x03, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(3, *cpu->getReg(3) << v + *cpu->getReg(3) >> (32 - v));
			}
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x03, 0x01}, 4)) cpu->setReg(3, *cpu->getReg(3) << *cpu->getReg(0) + *cpu->getReg(3) >> (32 - *cpu->getReg(0)));
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x03, 0x02}, 4)) cpu->setReg(3, *cpu->getReg(3) << *cpu->getReg(1) + *cpu->getReg(3) >> (32 - *cpu->getReg(1)));
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x03, 0x03}, 4)) cpu->setReg(3, *cpu->getReg(3) << *cpu->getReg(2) + *cpu->getReg(3) >> (32 - *cpu->getReg(2)));
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x03, 0x04}, 4)) cpu->setReg(3, *cpu->getReg(3) << *cpu->getReg(4) + *cpu->getReg(3) >> (32 - *cpu->getReg(4)));

			// LLT EEX, ...
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x04, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(4, *cpu->getReg(4) << v + *cpu->getReg(4) >> (32 - v));
			}
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x04, 0x01}, 4)) cpu->setReg(4, *cpu->getReg(4) << *cpu->getReg(0) + *cpu->getReg(4) >> (32 - *cpu->getReg(0)));
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x04, 0x02}, 4)) cpu->setReg(4, *cpu->getReg(4) << *cpu->getReg(1) + *cpu->getReg(4) >> (32 - *cpu->getReg(1)));
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x04, 0x03}, 4)) cpu->setReg(4, *cpu->getReg(4) << *cpu->getReg(2) + *cpu->getReg(4) >> (32 - *cpu->getReg(2)));
			else if(inst->chkInst(info.oplist, {0x09, 0x00, 0x04, 0x04}, 4)) cpu->setReg(4, *cpu->getReg(4) << *cpu->getReg(3) + *cpu->getReg(4) >> (32 - *cpu->getReg(3)));

			// RLT系
			// RLT EAX, ...
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x00, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(0, *cpu->getReg(0) >> v + *cpu->getReg(0) << (32 - v));
			}
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x00, 0x01}, 4)) cpu->setReg(0, *cpu->getReg(0) >> *cpu->getReg(1) + *cpu->getReg(0) << (32 - *cpu->getReg(1)));
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x00, 0x02}, 4)) cpu->setReg(0, *cpu->getReg(0) >> *cpu->getReg(2) + *cpu->getReg(0) << (32 - *cpu->getReg(2)));
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x00, 0x03}, 4)) cpu->setReg(0, *cpu->getReg(0) >> *cpu->getReg(3) + *cpu->getReg(0) << (32 - *cpu->getReg(3)));
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x00, 0x04}, 4)) cpu->setReg(0, *cpu->getReg(0) >> *cpu->getReg(4) + *cpu->getReg(0) << (32 - *cpu->getReg(4)));

			// RLT EBX, ...
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x01, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(1, *cpu->getReg(1) >> v + *cpu->getReg(1) << (32 - v));
			}
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x01, 0x01}, 4)) cpu->setReg(1, *cpu->getReg(1) >> *cpu->getReg(0) + *cpu->getReg(1) << (32 - *cpu->getReg(0)));
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x01, 0x02}, 4)) cpu->setReg(1, *cpu->getReg(1) >> *cpu->getReg(2) + *cpu->getReg(1) << (32 - *cpu->getReg(2)));
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x01, 0x03}, 4)) cpu->setReg(1, *cpu->getReg(1) >> *cpu->getReg(3) + *cpu->getReg(1) << (32 - *cpu->getReg(3)));
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x01, 0x04}, 4)) cpu->setReg(1, *cpu->getReg(1) >> *cpu->getReg(4) + *cpu->getReg(1) << (32 - *cpu->getReg(4)));
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x01, 0x05}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(8, *cpu->getReg(8) >> v + *cpu->getReg(8) << (32 - v));
			}
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x01, 0x06}, 4)) cpu->setReg(8, *cpu->getReg(8) >> *cpu->getReg(0) + *cpu->getReg(8) << (32 - *cpu->getReg(0)));
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x01, 0x07}, 4)) cpu->setReg(8, *cpu->getReg(8) >> *cpu->getReg(2) + *cpu->getReg(8) << (32 - *cpu->getReg(2)));
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x01, 0x08}, 4)) cpu->setReg(8, *cpu->getReg(8) >> *cpu->getReg(3) + *cpu->getReg(8) << (32 - *cpu->getReg(3)));
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x01, 0x09}, 4)) cpu->setReg(8, *cpu->getReg(8) >> *cpu->getReg(4) + *cpu->getReg(8) << (32 - *cpu->getReg(4)));

			// RLT ECX, ...
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x02, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(2, *cpu->getReg(2) >> v + *cpu->getReg(2) << (32 - v));
			}
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x02, 0x01}, 4)) cpu->setReg(2, *cpu->getReg(2) >> *cpu->getReg(0) + *cpu->getReg(2) << (32 - *cpu->getReg(0)));
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x02, 0x02}, 4)) cpu->setReg(2, *cpu->getReg(2) >> *cpu->getReg(1) + *cpu->getReg(2) << (32 - *cpu->getReg(1)));
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x02, 0x03}, 4)) cpu->setReg(2, *cpu->getReg(2) >> *cpu->getReg(3) + *cpu->getReg(2) << (32 - *cpu->getReg(3)));
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x02, 0x04}, 4)) cpu->setReg(2, *cpu->getReg(2) >> *cpu->getReg(4) + *cpu->getReg(2) << (32 - *cpu->getReg(4)));

			// RLT EDX, ...
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x03, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(3, *cpu->getReg(3) >> v + *cpu->getReg(3) << (32 - v));
			}
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x03, 0x01}, 4)) cpu->setReg(3, *cpu->getReg(3) >> *cpu->getReg(0) + *cpu->getReg(3) << (32 - *cpu->getReg(0)));
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x03, 0x02}, 4)) cpu->setReg(3, *cpu->getReg(3) >> *cpu->getReg(1) + *cpu->getReg(3) << (32 - *cpu->getReg(1)));
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x03, 0x03}, 4)) cpu->setReg(3, *cpu->getReg(3) >> *cpu->getReg(2) + *cpu->getReg(3) << (32 - *cpu->getReg(2)));
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x03, 0x04}, 4)) cpu->setReg(3, *cpu->getReg(3) >> *cpu->getReg(4) + *cpu->getReg(3) << (32 - *cpu->getReg(4)));

			// RLT EEX, ...
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x04, 0x00}, 4))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setReg(4, *cpu->getReg(4) >> v + *cpu->getReg(4) << (32 - v));
			}
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x04, 0x01}, 4)) cpu->setReg(4, *cpu->getReg(4) >> *cpu->getReg(0) + *cpu->getReg(4) << (32 - *cpu->getReg(0)));
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x04, 0x02}, 4)) cpu->setReg(4, *cpu->getReg(4) >> *cpu->getReg(1) + *cpu->getReg(4) << (32 - *cpu->getReg(1)));
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x04, 0x03}, 4)) cpu->setReg(4, *cpu->getReg(4) >> *cpu->getReg(2) + *cpu->getReg(4) << (32 - *cpu->getReg(2)));
			else if(inst->chkInst(info.oplist, {0x09, 0x01, 0x04, 0x04}, 4)) cpu->setReg(4, *cpu->getReg(4) >> *cpu->getReg(3) + *cpu->getReg(4) << (32 - *cpu->getReg(3)));

			// CMP系
			// CMP EAX, ...
			else if(inst->chkInst(info.oplist, {0x0A, 0x00, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				if(!(*cpu->getReg(0) - v))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(0) - v < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0A, 0x00, 0x01}, 3))
			{
				if(!(*cpu->getReg(0) - *cpu->getReg(0)))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(0) - *cpu->getReg(0) < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0A, 0x00, 0x02}, 3))
			{
				if(!(*cpu->getReg(0) - *cpu->getReg(1)))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(0) - *cpu->getReg(1) < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0A, 0x00, 0x03}, 3))
			{
				if(!(*cpu->getReg(0) - *cpu->getReg(2)))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(0) - *cpu->getReg(2) < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0A, 0x00, 0x04}, 3))
			{
				if(!(*cpu->getReg(0) - *cpu->getReg(3)))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(0) - *cpu->getReg(3) < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0A, 0x00, 0x05}, 3))
			{
				if(!(*cpu->getReg(0) - *cpu->getReg(4)))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(0) - *cpu->getReg(4) < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}

			// CMP EBX, ...
			else if(inst->chkInst(info.oplist, {0x0A, 0x01, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				if(!(*cpu->getReg(1) - v))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(1) - v < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0A, 0x01, 0x01}, 3))
			{
				if(!(*cpu->getReg(1) - *cpu->getReg(0)))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(1) - *cpu->getReg(0) < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0A, 0x01, 0x02}, 3))
			{
				if(!(*cpu->getReg(1) - *cpu->getReg(1)))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(1) - *cpu->getReg(1) < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0A, 0x01, 0x03}, 3))
			{
				if(!(*cpu->getReg(1) - *cpu->getReg(2)))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(1) - *cpu->getReg(2) < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0A, 0x01, 0x04}, 3))
			{
				if(!(*cpu->getReg(1) - *cpu->getReg(3)))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(1) - *cpu->getReg(3) < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0A, 0x01, 0x05}, 3))
			{
				if(!(*cpu->getReg(1) - *cpu->getReg(4)))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(1) - *cpu->getReg(4) < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}

			// CMP ECX, ...
			else if(inst->chkInst(info.oplist, {0x0A, 0x02, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				if(!(*cpu->getReg(2) - v))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(2) - v < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0A, 0x02, 0x01}, 3))
			{
				if(!(*cpu->getReg(2) - *cpu->getReg(0)))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(2) - *cpu->getReg(0) < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0A, 0x02, 0x02}, 3))
			{
				if(!(*cpu->getReg(2) - *cpu->getReg(1)))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(2) - *cpu->getReg(1) < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0A, 0x02, 0x03}, 3))
			{
				if(!(*cpu->getReg(2) - *cpu->getReg(2)))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(2) - *cpu->getReg(2) < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0A, 0x02, 0x04}, 3))
			{
				if(!(*cpu->getReg(2) - *cpu->getReg(3)))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(2) - *cpu->getReg(3) < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0A, 0x02, 0x05}, 3))
			{
				if(!(*cpu->getReg(2) - *cpu->getReg(4)))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(2) - *cpu->getReg(4) < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}

			// CMP EDX, ...
			else if(inst->chkInst(info.oplist, {0x0A, 0x03, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				if(!(*cpu->getReg(3) - v))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(3) - v < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0A, 0x03, 0x01}, 3))
			{
				if(!(*cpu->getReg(3) - *cpu->getReg(0)))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(3) - *cpu->getReg(0) < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0A, 0x03, 0x02}, 3))
			{
				if(!(*cpu->getReg(3) - *cpu->getReg(1)))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(3) - *cpu->getReg(1) < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0A, 0x03, 0x03}, 3))
			{
				if(!(*cpu->getReg(3) - *cpu->getReg(2)))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(3) - *cpu->getReg(2) < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0A, 0x03, 0x04}, 3))
			{
				if(!(*cpu->getReg(3) - *cpu->getReg(3)))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(3) - *cpu->getReg(3) < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0A, 0x03, 0x05}, 3))
			{
				if(!(*cpu->getReg(3) - *cpu->getReg(4)))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(3) - *cpu->getReg(4) < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}

			// CMP EEX, ...
			else if(inst->chkInst(info.oplist, {0x0A, 0x04, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				if(!(*cpu->getReg(4) - v))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(4) - v < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0A, 0x04, 0x01}, 3))
			{
				if(!(*cpu->getReg(4) - *cpu->getReg(0)))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(4) - *cpu->getReg(0) < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0A, 0x04, 0x02}, 3))
			{
				if(!(*cpu->getReg(4) - *cpu->getReg(1)))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(4) - *cpu->getReg(1) < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0A, 0x04, 0x03}, 3))
			{
				if(!(*cpu->getReg(4) - *cpu->getReg(2)))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(4) - *cpu->getReg(2) < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0A, 0x04, 0x04}, 3))
			{
				if(!(*cpu->getReg(4) - *cpu->getReg(3)))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(4) - *cpu->getReg(3) < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0A, 0x04, 0x05}, 3))
			{
				if(!(*cpu->getReg(4) - *cpu->getReg(4)))
				{
					cpu->setFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
				else if(*cpu->getReg(4) - *cpu->getReg(4) < 0)
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->setFlag(cpu->FLAG_S);
					cpu->setFlag(cpu->FLAG_C);
				}
				else
				{
					cpu->clrFlag(cpu->FLAG_Z);
					cpu->clrFlag(cpu->FLAG_S);
					cpu->clrFlag(cpu->FLAG_C);
				}
			}

			// JMP系
			// JMP...
			else if(inst->chkInst(info.oplist, {0x0B, 0x00, 0x00}, 3))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
				cpu->setPC(v);
			}
			else if(inst->chkInst(info.oplist, {0x0B, 0x00, 0x01}, 3)) cpu->setPC(*cpu->getReg(0));
			else if(inst->chkInst(info.oplist, {0x0B, 0x00, 0x02}, 3)) cpu->setPC(*cpu->getReg(1));
			else if(inst->chkInst(info.oplist, {0x0B, 0x00, 0x03}, 3)) cpu->setPC(*cpu->getReg(8));
			else if(inst->chkInst(info.oplist, {0x0B, 0x00, 0x04}, 3)) cpu->setPC(*cpu->getReg(2));
			else if(inst->chkInst(info.oplist, {0x0B, 0x00, 0x05}, 3)) cpu->setPC(*cpu->getReg(3));
			else if(inst->chkInst(info.oplist, {0x0B, 0x00, 0x06}, 3)) cpu->setPC(*cpu->getReg(4));

			// JZ...
			else if(inst->chkInst(info.oplist, {0x0B, 0x01, 0x00}, 3))
			{
				if(cpu->getFlag(cpu->FLAG_Z))
				{
					uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
					cpu->setPC(v);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0B, 0x01, 0x01}, 3)) if(cpu->getFlag(cpu->FLAG_Z)) cpu->setPC(*cpu->getReg(0)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x01, 0x02}, 3)) if(cpu->getFlag(cpu->FLAG_Z)) cpu->setPC(*cpu->getReg(1)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x01, 0x03}, 3)) if(cpu->getFlag(cpu->FLAG_Z)) cpu->setPC(*cpu->getReg(8)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x01, 0x04}, 3)) if(cpu->getFlag(cpu->FLAG_Z)) cpu->setPC(*cpu->getReg(2)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x01, 0x05}, 3)) if(cpu->getFlag(cpu->FLAG_Z)) cpu->setPC(*cpu->getReg(3)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x01, 0x06}, 3)) if(cpu->getFlag(cpu->FLAG_Z)) cpu->setPC(*cpu->getReg(4)); else;

			// JS...
			else if(inst->chkInst(info.oplist, {0x0B, 0x02, 0x00}, 3))
			{
				if(cpu->getFlag(cpu->FLAG_S) && cpu->getFlag(cpu->FLAG_C))
				{
					uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
					cpu->setPC(v);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0B, 0x02, 0x01}, 3)) if(cpu->getFlag(cpu->FLAG_S) && cpu->getFlag(cpu->FLAG_C)) cpu->setPC(*cpu->getReg(0)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x02, 0x02}, 3)) if(cpu->getFlag(cpu->FLAG_S) && cpu->getFlag(cpu->FLAG_C)) cpu->setPC(*cpu->getReg(1)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x02, 0x03}, 3)) if(cpu->getFlag(cpu->FLAG_S) && cpu->getFlag(cpu->FLAG_C)) cpu->setPC(*cpu->getReg(8)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x02, 0x04}, 3)) if(cpu->getFlag(cpu->FLAG_S) && cpu->getFlag(cpu->FLAG_C)) cpu->setPC(*cpu->getReg(2)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x02, 0x05}, 3)) if(cpu->getFlag(cpu->FLAG_S) && cpu->getFlag(cpu->FLAG_C)) cpu->setPC(*cpu->getReg(3)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x02, 0x06}, 3)) if(cpu->getFlag(cpu->FLAG_S) && cpu->getFlag(cpu->FLAG_C)) cpu->setPC(*cpu->getReg(4)); else;

			// JC...
			else if(inst->chkInst(info.oplist, {0x0B, 0x03, 0x00}, 3))
			{
				if(cpu->getFlag(cpu->FLAG_C))
				{
					uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
					cpu->setPC(v);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0B, 0x03, 0x01}, 3)) if(cpu->getFlag(cpu->FLAG_C)) cpu->setPC(*cpu->getReg(0)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x03, 0x02}, 3)) if(cpu->getFlag(cpu->FLAG_C)) cpu->setPC(*cpu->getReg(1)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x03, 0x03}, 3)) if(cpu->getFlag(cpu->FLAG_C)) cpu->setPC(*cpu->getReg(8)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x03, 0x04}, 3)) if(cpu->getFlag(cpu->FLAG_C)) cpu->setPC(*cpu->getReg(2)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x03, 0x05}, 3)) if(cpu->getFlag(cpu->FLAG_C)) cpu->setPC(*cpu->getReg(3)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x03, 0x06}, 3)) if(cpu->getFlag(cpu->FLAG_C)) cpu->setPC(*cpu->getReg(4)); else;

			// JNZ...
			else if(inst->chkInst(info.oplist, {0x0B, 0x04, 0x00}, 3))
			{
				if(!cpu->getFlag(cpu->FLAG_Z))
				{
					uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
					cpu->setPC(v);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0B, 0x04, 0x01}, 3)) if(!cpu->getFlag(cpu->FLAG_Z)) cpu->setPC(*cpu->getReg(0)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x04, 0x02}, 3)) if(!cpu->getFlag(cpu->FLAG_Z)) cpu->setPC(*cpu->getReg(1)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x04, 0x03}, 3)) if(!cpu->getFlag(cpu->FLAG_Z)) cpu->setPC(*cpu->getReg(8)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x04, 0x04}, 3)) if(!cpu->getFlag(cpu->FLAG_Z)) cpu->setPC(*cpu->getReg(2)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x04, 0x05}, 3)) if(!cpu->getFlag(cpu->FLAG_Z)) cpu->setPC(*cpu->getReg(3)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x04, 0x06}, 3)) if(!cpu->getFlag(cpu->FLAG_Z)) cpu->setPC(*cpu->getReg(4)); else;

			// JNS...
			else if(inst->chkInst(info.oplist, {0x0B, 0x05, 0x00}, 3))
			{
				if(!(cpu->getFlag(cpu->FLAG_S) && cpu->getFlag(cpu->FLAG_C)))
				{
					uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
					cpu->setPC(v);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0B, 0x05, 0x01}, 3)) if(!(cpu->getFlag(cpu->FLAG_S) && cpu->getFlag(cpu->FLAG_C))) cpu->setPC(*cpu->getReg(0)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x05, 0x02}, 3)) if(!(cpu->getFlag(cpu->FLAG_S) && cpu->getFlag(cpu->FLAG_C))) cpu->setPC(*cpu->getReg(1)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x05, 0x03}, 3)) if(!(cpu->getFlag(cpu->FLAG_S) && cpu->getFlag(cpu->FLAG_C))) cpu->setPC(*cpu->getReg(8)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x05, 0x04}, 3)) if(!(cpu->getFlag(cpu->FLAG_S) && cpu->getFlag(cpu->FLAG_C))) cpu->setPC(*cpu->getReg(2)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x05, 0x05}, 3)) if(!(cpu->getFlag(cpu->FLAG_S) && cpu->getFlag(cpu->FLAG_C))) cpu->setPC(*cpu->getReg(3)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x05, 0x06}, 3)) if(!(cpu->getFlag(cpu->FLAG_S) && cpu->getFlag(cpu->FLAG_C))) cpu->setPC(*cpu->getReg(4)); else;

			// JNC...
			else if(inst->chkInst(info.oplist, {0x0B, 0x06, 0x00}, 3))
			{
				if(!cpu->getFlag(cpu->FLAG_C))
				{
					uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);
					cpu->setPC(v);
				}
			}
			else if(inst->chkInst(info.oplist, {0x0B, 0x06, 0x01}, 3)) if(!cpu->getFlag(cpu->FLAG_C)) cpu->setPC(*cpu->getReg(0)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x06, 0x02}, 3)) if(!cpu->getFlag(cpu->FLAG_C)) cpu->setPC(*cpu->getReg(1)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x06, 0x03}, 3)) if(!cpu->getFlag(cpu->FLAG_C)) cpu->setPC(*cpu->getReg(8)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x06, 0x04}, 3)) if(!cpu->getFlag(cpu->FLAG_C)) cpu->setPC(*cpu->getReg(2)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x06, 0x05}, 3)) if(!cpu->getFlag(cpu->FLAG_C)) cpu->setPC(*cpu->getReg(3)); else;
			else if(inst->chkInst(info.oplist, {0x0B, 0x06, 0x06}, 3)) if(!cpu->getFlag(cpu->FLAG_C)) cpu->setPC(*cpu->getReg(4)); else;

			// CALL系
			else if(inst->chkInst(info.oplist, {0x0C, 0x00}, 2))
			{
				uint32_t v = readImm(cpu->getPC() + info.len, info.immLen);

				uint32_t tmp = *cpu->getReg(4);
				cpu->setReg(4, cpu->getPC() + info.len + info.immLen);
				push(4);
				cpu->setReg(4, tmp);
				cpu->setPC(v);
			}
			else if(inst->chkInst(info.oplist, {0x0C, 0x01}, 3))
			{
				uint32_t tmp = *cpu->getReg(4);
				cpu->setReg(4, cpu->getPC() + info.len);
				push(4);
				cpu->setReg(4, tmp);
				cpu->setPC(*cpu->getReg(0));
			}
			else if(inst->chkInst(info.oplist, {0x0C, 0x02}, 3))
			{
				uint32_t tmp = *cpu->getReg(4);
				cpu->setReg(4, cpu->getPC() + info.len);
				push(4);
				cpu->setReg(4, tmp);
				cpu->setPC(*cpu->getReg(1));
			}
			else if(inst->chkInst(info.oplist, {0x0C, 0x03}, 3))
			{
				uint32_t tmp = *cpu->getReg(4);
				cpu->setReg(4, cpu->getPC() + info.len);
				push(4);
				cpu->setReg(4, tmp);
				cpu->setPC(*cpu->getReg(2));
			}
			else if(inst->chkInst(info.oplist, {0x0C, 0x04}, 3))
			{
				uint32_t tmp = *cpu->getReg(4);
				cpu->setReg(4, cpu->getPC() + info.len);
				push(4);
				cpu->setReg(4, tmp);
				cpu->setPC(*cpu->getReg(3));
			}
			else if(inst->chkInst(info.oplist, {0x0C, 0x05}, 3))
			{
				uint32_t tmp = *cpu->getReg(4);
				cpu->setReg(4, cpu->getPC() + info.len);
				push(4);
				cpu->setReg(4, tmp);
				cpu->setPC(*cpu->getReg(4));
			}

			// PUSH系
			else if(inst->chkInst(info.oplist, {0x0D, 0x00, 0x00}, 3)) push(0);
			else if(inst->chkInst(info.oplist, {0x0D, 0x00, 0x01}, 3)) push(1);
			else if(inst->chkInst(info.oplist, {0x0D, 0x00, 0x02}, 3)) push(2);
			else if(inst->chkInst(info.oplist, {0x0D, 0x00, 0x03}, 3)) push(3);
			else if(inst->chkInst(info.oplist, {0x0D, 0x00, 0x04}, 3)) push(4);
			else if(inst->chkInst(info.oplist, {0x0D, 0x00, 0x05}, 3)) push(5);
			else if(inst->chkInst(info.oplist, {0x0D, 0x00, 0x06}, 3)) push(6);

			// POP系
			else if(inst->chkInst(info.oplist, {0x0D, 0x01, 0x00}, 3)) pop(0);
			else if(inst->chkInst(info.oplist, {0x0D, 0x01, 0x01}, 3)) pop(1);
			else if(inst->chkInst(info.oplist, {0x0D, 0x01, 0x02}, 3)) pop(2);
			else if(inst->chkInst(info.oplist, {0x0D, 0x01, 0x03}, 3)) pop(3);
			else if(inst->chkInst(info.oplist, {0x0D, 0x01, 0x04}, 3)) pop(4);
			else if(inst->chkInst(info.oplist, {0x0D, 0x01, 0x05}, 3)) pop(5);
			else if(inst->chkInst(info.oplist, {0x0D, 0x01, 0x06}, 3)) pop(6);

			// RET
			else if(inst->chkInst(info.oplist, {0x0E}, 1))
			{
				uint32_t tmp = *cpu->getReg(4);
				uint32_t ump = 0;

				pop(4);
				ump = *cpu->getReg(4);
				cpu->setReg(4, tmp);

				cpu->setPC(ump);
			}

			// HALT
			else if(inst->chkInst(info.oplist, {0x0F}, 1)) if(cpu->chkIRQ(~0));
			else return false;

			cpu->setPC(cpu->getPC() + info.len);
			if(info.hasImm) cpu->setPC(cpu->getPC() + info.immLen);

			return true;
		}
};

#endif
