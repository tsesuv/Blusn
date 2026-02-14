#ifndef US_MEM
#define US_MEM

#include "xvm.inc"

////////////////////////////////////////////////////////

class MEM
{
	private:
		uint8_t *dat;
		uint32_t size;

	public:
		bool init(uint32_t memSize)
		{
			dat = (uint8_t *)malloc(memSize);
			if(dat == nullptr) return false;

			size = memSize;
			memset(dat, 0, size);

			return true;
		}

		bool free(void)
		{
			if(dat != nullptr)
			{
				::free(dat);
				dat = nullptr;
				size = 0;
			}

			return true;
		}

		bool isValid(uint32_t addr, uint32_t len)
		{
			return !(size < addr + len);
		}

		bool readBit(uint32_t addr, uint8_t bitPos, bool *out)
		{
			if(!isValid(addr, 1) || !(bitPos < 8)) return false;

			*out = (dat[addr] & (1 << bitPos)) != 0;

			return true;
		}

		bool readHalf(uint32_t addr, bool isHigh, uint8_t *out)
		{
			if(!isValid(addr, 1)) return false;

			if(isHigh) *out = (dat[addr] >> 4) & 0x0F;
			else *out = dat[addr] & 0x0F;

			return true;
		}

		bool readByte(uint32_t addr, uint8_t *out)
		{
			if(!isValid(addr, 1)) return false;

			*out = dat[addr];

			return true;
		}

		bool readWord(uint32_t addr, uint16_t *out)
		{
			if(!isValid(addr, 2)) return false;

			*out = ((uint16_t)dat[addr] << 8) | dat[addr + 1];

			return true;
		}

		bool readDouble(uint32_t addr, uint32_t *out)
		{
			if(!isValid(addr, 4)) return false;

			*out = ((uint32_t)dat[addr] << 24) | ((uint32_t)dat[addr + 1] << 16) | ((uint32_t)dat[addr + 2] << 8) | dat[addr + 3];

			return true;
		}

		bool writeBit(uint32_t addr, uint8_t bitPos, bool val)
		{
			if(!isValid(addr, 1) || !(bitPos < 8)) return false;

			if(val) dat[addr] |= (1 << bitPos);
			else dat[addr] &= ~(1 << bitPos);

			return true;
		}

		bool writeHalf(uint32_t addr, bool isHigh, uint8_t val)
		{
			if(!isValid(addr, 1)) return false;

			if(isHigh) dat[addr] = (dat[addr] & 0x0F) | ((val & 0x0F) << 4);
			else dat[addr] = (dat[addr] & 0xF0) | (val & 0x0F);

			return true;
		}

		bool writeByte(uint32_t addr, uint8_t val)
		{
			if(!isValid(addr, 1)) return false;

			dat[addr] = val;

			return true;
		}

		bool writeWord(uint32_t addr, uint16_t val)
		{
			if(!isValid(addr, 2)) return false;

			dat[addr] = (val >> 8) & 0xFF;
			dat[addr + 1] = val & 0xFF;

			return true;
		}

		bool writeDouble(uint32_t addr, uint32_t val)
		{
			if(!isValid(addr, 4)) return false;

			dat[addr] = (val >> 24) & 0xFF;
			dat[addr + 1] = (val >> 16) & 0xFF;
			dat[addr + 2] = (val >> 8) & 0xFF;
			dat[addr + 3] = val & 0xFF;

			return true;
		}
};

#endif /* mem.inc */
