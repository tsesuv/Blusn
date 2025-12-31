#ifndef US_CPU
#define US_CPU

#include "xvm.inc"
#include "mem.inc"

////////////////////////////////////////////////////////

class CPU
{
	private:
		uint32_t EAX;
		uint32_t EBX;
		uint32_t ECX;
		uint32_t EDX;
		uint32_t EEX;
		uint32_t EDI;
		uint32_t ESI;
		uint32_t EBP;

		uint32_t F;
		uint32_t SP;
		uint32_t CS;
		uint32_t DS;
		uint32_t SS;
		uint32_t PC;

		uint32_t irq;

		MEM *mem;

	public:
		static const uint32_t FLAG_Z = 0x01; // Zero
		static const uint32_t FLAG_S = 0x02; // Sign
		static const uint32_t FLAG_C = 0x04; // Carry

		static const uint32_t IRQ_TIMER = 0x01;
		static const uint32_t IRQ_IO = 0x02;
		static const uint32_t IRQ_BLOCKING = 0x04;

		bool initMem(MEM *memP)
		{
			mem = memP;

			return true;
		}

		bool setReg(int regID, uint32_t dat)
		{
			switch(regID)
			{
				case 0:
					EAX = dat;
					return true;
				case 1:
					EBX = dat;
					return true;
				case 2:
					ECX = dat;
					return true;
				case 3:
					EDX = dat;
					return true;
				case 4:
					EEX = dat;
					return true;
				case 5:
					EDI = dat;
					return true;
				case 6:
					ESI = dat;
					return true;
				case 7:
					EBP = dat;
					return true;
				case 8: return mem->writeDouble(EBX, dat);
				case 9: return mem->writeDouble(EDI, dat);
				case 10: return mem->writeDouble(ESI, dat);
				case 11: return mem->writeDouble(EBP, dat);
				default: return false;
			}
		}

		uint32_t *getReg(int regID)
		{
			static uint32_t tmp;

			switch(regID)
			{
				case 0: return &EAX;
				case 1: return &EBX;
				case 2: return &ECX;
				case 3: return &EDX;
				case 4: return &EEX;
				case 5: return &EDI;
				case 6: return &ESI;
				case 7: return &EBP;
				case 8:
					mem->readDouble(EBX, &tmp);
					return &tmp;
				case 9:
					mem->readDouble(EDI, &tmp);
					return &tmp;
				case 10:
					mem->readDouble(ESI, &tmp);
					return &tmp;
				case 11:
					mem->readDouble(EBP, &tmp);
					return &tmp;
				default: return nullptr;
			}
		}

		bool setFlag(uint32_t flag)
		{
			F |= flag;

			return true;
		}

		bool clrFlag(uint32_t flag)
		{
			F &= ~flag;

			return true;
		}

		bool getFlag(uint32_t flag)
		{
			return (F & flag) != 0;
		}

		bool setIRQ(uint32_t irqBit)
		{
			irq |= irqBit;

			return true;
		}

		bool clrIRQ(uint32_t irqBit)
		{
			irq &= ~irqBit;

			return true;
		}

		bool chkIRQ(uint32_t irqBit)
		{
			return (irq & irqBit) != 0;
		}

		bool setPC(uint32_t addr)
		{
			PC = addr;

			return true;
		}

		uint32_t getPC(void)
		{
			return PC;
		}

		bool pushSP(uint8_t len)
		{
			SP -= len;

			return true;
		}

		bool popSP(uint8_t len)
		{
			SP += len;

			return true;
		}

		uint32_t getSP(void)
		{
			return SP;
		}

		bool reset(void)
		{
			setIRQ(IRQ_BLOCKING);

			EAX = 0;
			EBX = 0;
			ECX = 0;
			EDX = 0;
			EEX = 0;
			EDI = 0;
			ESI = 0;
			EBP = 0;
			F = 0;
			SP = (uint32_t)-1;
			CS = 0;
			DS = 0;
			SS = 0;
			PC = 0;
			irq = 4;

			clrIRQ(IRQ_BLOCKING);

			return true;
		}
};


#endif
