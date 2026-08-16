/* XMC Virtual Machine Version:1.0.2 Master Release */
/* XMC: Xross(Cross) Machine Code */
#define K * 1024
#define M K K
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#endif

uint16_t pc = 0, sp = 0;
uint8_t memory[8 M - 1] = {0};
uint8_t a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, h = 0, l = 0, bp = 0;
FILE *infile;
uint32_t FILESIZE = 0;

void version()
{
	printf("XMC Virtual Machine Version:1.0.2 Master Release\n");
	printf("Created by vijeg dosmen(or aRefOOT2)\n");
	printf("Enter 'xvm /?` you get more helps.\n");
	exit(0);
}

void help()
{
	printf("XMC Virtual Machine\n");
	printf("Usage:\n");
	printf("	xvm [/i [Input file path]] [Options]\n");
	printf("Options:\n");
	printf("	/i Enter the input XMC file path.\n");
	printf("	/? This help message.\n");
	printf("	/v Print software informations.\n");
	exit(0);
}

void syscall(uint8_t number)
{
	switch(number)
	{
		case 0:
			break;
		case 1:
			exit(d);
			break;
		case 2:
			printf("%c", (char)d);
			break;
		case 3:
			if(kbhit())
			d = getch();
			break;
		case 4:
			int tmp = d;
			while(d == tmp){d = getch();};
			break;
		case 5:
			while(1);
			break;
		default:
			printf("Undefined syscall: %X\n", number);
			break;
	}
}

void exec(uint8_t* p)
{
	volatile uint8_t NOP_COUNTER;
	while(pc + (bp << 16) < 8 M)
	{
		switch(*(p + pc + (bp << 16)))
		{
			case 0x00:
				NOP_COUNTER = 0;
				for(int NOP_TEMP = 0; NOP_TEMP < 64; NOP_TEMP++)
				{
					NOP_COUNTER += NOP_COUNTER;
				}
				break;
			case 0x01:
				a = b;
				break;
			case 0x02:
				a = c;
				break;
			case 0x03:
				a = d;
				break;
			case 0x04:
				a = e;
				break;
			case 0x05:
				b = a;
				break;
			case 0x06:
				b = c;
				break;
			case 0x07:
				b = d;
				break;
			case 0x08:
				b = e;
				break;
			case 0x09:
				c = a;
				break;
			case 0x0A:
				c = b;
				break;
			case 0x0B:
				c = d;
				break;
			case 0x0C:
				c = e;
				break;
			case 0x0D:
				d = a;
				break;
			case 0x0E:
				d = b;
				break;
			case 0x0F:
				d = c;
			case 0x10:
				d = e;
				break;
			case 0x11:
				e = a;
				break;
			case 0x12:
				e = b;
				break;
			case 0x13:
				e = c;
				break;
			case 0x14:
				e = d;
				break;
			case 0x15:
				d = *(p + pc + (bp << 16) + 1);
				pc++;
				break;
			case 0x16:
				e = *(p + pc + (bp << 16) + 1);
				pc++;
				break;
			case 0x17:
				e = bp;
				break;
			case 0x18:
				bp = e;
				break;
			case 0x19:
				h = b;
				l = c;
				break;
			case 0x1A:
				h = d;
				l = e;
				break;
			case 0x1B:
				b = h;
				c = l;
				break;
			case 0x1C:
				d = h;
				e = l;
				break;
			case 0x1D:
				h = *(p + pc + (bp << 16) + 2);
				l = *(p + pc + (bp << 16) + 1);
				pc += 2;
				break;
			case 0x1E:
				h = sp >> 4;
				l = sp % 0x10;
				break;
			case 0x1F:
				h = (pc + (bp << 16)) >> 4;
				l = pc + (bp << 16) % 0x100;
				break;
			case 0x20:
				p[(p[pc + (bp << 16) + 3] << 4) + p[pc + (bp << 16) + 2] + (p[pc + (bp << 16) + 1] << 16)] = a;
				pc += 3;
				break;
			case 0x21:
				p[(p[pc + (bp << 16) + 3] << 4) + p[pc + (bp << 16) + 2] + (p[pc + (bp << 16) + 1] << 16)] = d;
				pc += 3;
				break;
			case 0x22:
				p[(p[pc + (bp << 16) + 3] << 4) + p[pc + (bp << 16) + 2] + (p[pc + (bp << 16) + 1] << 16)] = e;
				pc += 3;
				break;
			case 0x23:
				p[(h << 4) + l + p[pc + (bp << 16) + 1]] = a;
				pc++;
				break;
			case 0x24:
				p[(h << 4) + l + p[pc + (bp << 16) + 1]] = d;
				pc++;
				break;
			case 0x25:
				p[(h << 4) + l + p[pc + (bp << 16) + 1]] = e;
				pc++;
				break;
			case 0x26:
				a = p[(p[pc + (bp << 16) + 3] << 4) + p[pc + (bp << 16) + 2] + (p[pc + (bp << 16) + 1] << 16)];
				pc += 3;
				break;
			case 0x27:
				d = p[(p[pc + (bp << 16) + 3] << 4) + p[pc + (bp << 16) + 2] + (p[pc + (bp << 16) + 1] << 16)];
				pc += 3;
				break;
			case 0x28:
				e = p[(p[pc + (bp << 16) + 3] << 4) + p[pc + (bp << 16) + 2] + (p[pc + (bp << 16) + 1] << 16)];
				pc += 3;
				break;
			case 0x29:
				a = p[(h << 4) + l + p[pc + (bp << 16) + 1]];
				pc++;
				break;
			case 0x2A:
				d = p[(h << 4) + l + p[pc + (bp << 16) + 1]];
				pc++;
				break;
			case 0x2B:
				e = p[(h << 4) + l + p[pc + (bp << 16) + 1]];
				pc++;
				break;
			case 0x2C:
				f = (f || 0x04) - (f && 0x04);
				if(a && 0xFF == 0xFF)
				f = f || 0x04;
				a += b;
				a = a % 0x100;
				break;
			case 0x2D:
				f = (f || 0x04) - (f && 0x04);
				if(a && 0xFF == 0xFF)
				f = f || 0x04;
				a += c;
				a = a % 0x100;
				break;
			case 0x2E:
				f = (f || 0x04) - (f && 0x04);
				if(a && 0xFF == 0xFF)
				f = f || 0x04;
				a += d;
				a = a % 0x100;
				break;
			case 0x2F:
				f = (f || 0x04) - (f && 0x04);
				if(a && 0xFF == 0xFF)
				f = f || 0x04;
				a += e;
				a = a % 0x100;
				break;
			case 0x30:
				f = (f || 0x04) - (f && 0x04);
				if(b && 0xFF == 0xFF)
				f = f || 0x04;
				b += a;
				b = b % 0x100;
				break;
			case 0x31:
				f = (f || 0x04) - (f && 0x04);
				if(b && 0xFF == 0xFF)
				f = f || 0x04;
				b += c;
				b = b % 0x100;
				break;
			case 0x32:
				f = (f || 0x04) - (f && 0x04);
				if(b && 0xFF == 0xFF)
				f = f || 0x04;
				b += d;
				b = b % 0x100;
				break;
			case 0x33:
				f = (f || 0x04) - (f && 0x04);
				if(b && 0xFF == 0xFF)
				f = f || 0x04;
				b += e;
				b = b % 0x100;
				break;
			case 0x34:
				f = (f || 0x04) - (f && 0x04);
				if(c && 0xFF == 0xFF)
				f = f || 0x04;
				c += a;
				c = c % 0x100;
				break;
			case 0x35:
				f = (f || 0x04) - (f && 0x04);
				if(c && 0xFF == 0xFF)
				f = f || 0x04;
				c += b;
				c = c % 0x100;
				break;
			case 0x36:
				f = (f || 0x04) - (f && 0x04);
				if(c && 0xFF == 0xFF)
				f = f || 0x04;
				c += d;
				c = c % 0x100;
				break;
			case 0x37:
				f = (f || 0x04) - (f && 0x04);
				if(c && 0xFF == 0xFF)
				f = f || 0x04;
				c += e;
				c = c % 0x100;
				break;
			case 0x38:
				f = (f || 0x04) - (f && 0x04);
				if(d && 0xFF == 0xFF)
				f = f || 0x04;
				d += a;
				d = d % 0x100;
				break;
			case 0x39:
				f = (f || 0x04) - (f && 0x04);
				if(d && 0xFF == 0xFF)
				f = f || 0x04;
				d += b;
				d = d % 0x100;
				break;
			case 0x3A:
				f = (f || 0x04) - (f && 0x04);
				if(d && 0xFF == 0xFF)
				f = f || 0x04;
				d += c;
				d = d % 0x100;
				break;
			case 0x3B:
				f = (f || 0x04) - (f && 0x04);
				if(d && 0xFF == 0xFF)
				f = f || 0x04;
				d += e;
				d = d % 0x100;
				break;
			case 0x3C:
				f = (f || 0x04) - (f && 0x04);
				if(e && 0xFF == 0xFF)
				f = f || 0x04;
				e += a;
				e = e % 0x100;
				break;
			case 0x3D:
				f = (f || 0x04) - (f && 0x04);
				if(e && 0xFF == 0xFF)
				f = f || 0x04;
				e += b;
				e = e % 0x100;
				break;
			case 0x3E:
				f = (f || 0x04) - (f && 0x04);
				if(e && 0xFF == 0xFF)
				f = f || 0x04;
				e += c;
				e = e % 0x100;
				break;
			case 0x3F:
				f = (f || 0x04) - (f && 0x04);
				if(d && 0xFF == 0xFF)
				f = f || 0x04;
				e += d;
				e = e % 0x100;
				break;
			case 0x40:
				f = (f || 0x04) - (f && 0x04);
				if(a < b)
				f = f || 0x04;
				a += ~(b) + 1;
				break;
			case 0x41:
				f = (f || 0x04) - (f && 0x04);
				if(a < c)
				f = f || 0x04;
				a += ~(c) + 1;
				break;
			case 0x42:
				f = (f || 0x04) - (f && 0x04);
				if(a < d)
				f = f || 0x04;
				a += ~(d) + 1;
				break;
			case 0x43:
				f = (f || 0x04) - (f && 0x04);
				if(a < e)
				f = f || 0x04;
				a += ~(e) + 1;
				break;
			case 0x44:
				f = (f || 0x04) - (f && 0x04);
				if(b < a)
				f = f || 0x04;
				b += ~(a) + 1;
				break;
			case 0x45:
				f = (f || 0x04) - (f && 0x04);
				if(b < c)
				f = f || 0x04;
				b += ~(c) + 1;
				break;
			case 0x46:
				f = (f || 0x04) - (f && 0x04);
				if(b < d)
				f = f || 0x04;
				b += ~(d) + 1;
				break;
			case 0x47:
				f = (f || 0x04) - (f && 0x04);
				if(b < e)
				f = f || 0x04;
				b += ~(e) + 1;
				break;
			case 0x48:
				f = (f || 0x04) - (f && 0x04);
				if(c < a)
				f = f || 0x04;
				c += ~(a) + 1;
				break;
			case 0x49:
				f = (f || 0x04) - (f && 0x04);
				if(c < b)
				f = f || 0x04;
				c += ~(b) + 1;
				break;
			case 0x4A:
				f = (f || 0x04) - (f && 0x04);
				if(c < d)
				f = f || 0x04;
				c += ~(d) + 1;
				break;
			case 0x4B:
				f = (f || 0x04) - (f && 0x04);
				if(c < e)
				f = f || 0x04;
				c += ~(e) + 1;
				break;
			case 0x4C:
				f = (f || 0x04) - (f && 0x04);
				if(d < a)
				f = f || 0x04;
				d += ~(a) + 1;
				break;
			case 0x4D:
				f = (f || 0x04) - (f && 0x04);
				if(d < b)
				f = f || 0x04;
				d += ~(b) + 1;
				break;
			case 0x4E:
				f = (f || 0x04) - (f && 0x04);
				if(d < c)
				f = f || 0x04;
				d += ~(c) + 1;
				break;
			case 0x4F:
				f = (f || 0x04) - (f && 0x04);
				if(d < e)
				f = f || 0x04;
				d += ~(e) + 1;
				break;
			case 0x50:
				f = (f || 0x04) - (f && 0x04);
				if(e < a)
				f = f || 0x04;
				e += ~(a) + 1;
				break;
			case 0x51:
				f = (f || 0x04) - (f && 0x04);
				if(e < b)
				f = f || 0x04;
				e += ~(b) + 1;
				break;
			case 0x52:
				f = (f || 0x04) - (f && 0x04);
				if(e < c)
				f = f || 0x04;
				e += ~(c) + 1;
				break;
			case 0x53:
				f = (f || 0x04) - (f && 0x04);
				if(e < d)
				f = f || 0x04;
				d += ~(d) + 1;
				break;
			case 0x54:
				d = d || e;
				break;
			case 0x55:
				d = d && e;
				break;
			case 0x56:
				d = (d || e) - (d && e);
				break;
			case 0x57:
				d = ~d;
				break;
			case 0x58:
				d = (d << 4) + (d >> 4);
				break;
			case 0x59:
				if(d && 0x80 == 0x80)
				f = f || 0x04;
				d = (d << 1) % 0x100;
				break;
			case 0x5A:
				if(d && 0x01 == 1)
				f = f || 0x04;
				d = (d >> 1) % 0x100;
				break;
			case 0x5B:
				if(d && 0x80 == 0x80)
				f = f || 0x04;
				d = (d << 1) % 0x100 + (d >> 7) % 0x100;
				break;
			case 0x5C:
				if(d && 0x01 == 0x01)
				f = f || 0x04;
				d = (d >> 1) % 0x100 + (d << 7) % 0x100;
				break;
			case 0x5D:
				f = (f || p[pc + (bp << 16)]) - (f && p[pc + (bp << 16)]);
				pc++;
				break;
			case 0x5E:
				if(b == p[pc + (bp << 16) + 1])
				f = f || 0x08;
				else
				f = (f || 0x08) - (f && 0x08);
				pc++;
				break;
			case 0x5F:
				if(b == d)
				f = f || 0x08;
				else
				f = (f || 0x08) - (f && 0x08);
				break;
			case 0x60:
				if(d < p[pc + (bp << 16) + 1])
				f = f || 0x01;
				else
				f = (f || 0x01) - (f && 0x01);
				pc++;
				break;
			case 0x61:
				if(d < e)
				f = f || 0x01;
				else
				f = (f || 0x01) - (f && 0x01);
				break;
			case 0x62:
				if(f && p[pc + (bp << 16) + 1] != 0)
				f = f || 0x02;
				else
				f = (f || 0x02) - (f && 0x02);
				pc++;
				break;
			case 0x63:
				pc = (((p[pc + (bp << 16) + 3] << 4)) + p[pc + (bp << 16) + 2]) + 1;
				bp = p[pc + (bp << 16) + 1];
				break;
			case 0x64:
				if(e && 0x80 == 0)
				pc += e;
				else
				pc += ~(e);
				break;
			case 0x65:
				if(f && 0x01 == 0x01)
				{
					if(e && 0x80 == 0)
					pc += e;
					else
					pc += ~(e);
				}
				break;
			case 0x66:
				if(f && 0x04 == 0x04)
				{
					if(e && 0x80 == 0)
					pc += e;
					else
					pc += ~(e);
				}
				break;
			case 0x67:
				if((f && 0x08 == 0x08))
				{
					if(e && 0x80 == 0)
					pc += e;
					else
					pc += ~(e);
				}
				break;
			case 0x68:
				if((f && p[pc + (bp << 16) + 1]) == p[pc + (bp << 16) + 1])
				{
					if(e && 0x80 == 0)
					pc += e;
					else
					pc += ~(e);
				}
				break;
			case 0x69:
				sp++;
				p[8 M - sp] = pc + (bp << 16);
				pc = ((h << 4) + l);
				break;
			case 0x6A:
				sp++;
				p[8 M - sp] = a;
				break;
			case 0x6B:
				sp++;
				p[8 M - sp] = b;
				break;
			case 0x6C:
				sp++;
				p[8 M - sp] = c;
				break;
			case 0x6D:
				sp++;
				p[8 M - sp] = d;
				break;
			case 0x6E:
				sp++;
				p[8 M - sp] = e;
				break;
			case 0x6F:
				sp++;
				p[8 M - sp] = h;
				break;
			case 0x70:
				sp++;
				p[8 M - sp] = l;
				break;
			case 0x71:
				sp--;
				a = p[8 M - sp];
				break;
			case 0x72:
				sp--;
				b = p[8 M - sp];
				break;
			case 0x73:
				sp--;
				c = p[8 M - sp];
				break;
			case 0x74:
				sp--;
				d = p[8 M - sp];
				break;
			case 0x75:
				sp--;
				e = p[8 M - sp];
				break;
			case 0x76:
				sp--;
				h = p[8 M - sp];
				break;
			case 0x77:
				sp--;
				l = p[8 M - sp];
				break;
			case 0x78:
				sp--;
				pc = p[8 M - sp];
				break;
			case 0x79:
				syscall(a);
				break;
			default:
				printf("Undefined XMC: %X\n", p[pc + (bp << 16)]);
				break;
		}
		pc++;
		if(pc > 64 K - 2)
		bp++;
	}
	return;
}

int main(int argc, char** argv)
{
	for(int i = 0; i < argc; i++)
	{
		if(strcmp(*(argv + i), "/v") == 0)
		{
			version();
		}
		if(strcmp(*(argv + i), "/?") == 0)
		{
			help();
		}
		if(strcmp(*(argv + i), "/i") == 0)
		{
			infile = fopen(*(argv + i + 1), "rb");

			if(infile == NULL)
			{
				printf("[ ERROR ] fopen: Can't open file: %s", *(argv + i + 1));
				exit(1);
			}
		}
	}

	size_t ReadFlag = 1;
	while(ReadFlag > 0)
	{
		ReadFlag = fread(&memory[FILESIZE], sizeof(uint8_t), 1, infile);
		FILESIZE++;
	}
	fclose(infile);
	f = 0x80;
	syscall(3);
	syscall(2);
	exec(memory);
	return 0;
}
