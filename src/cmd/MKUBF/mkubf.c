/* UnSynk Bmp Font Maker */
/* Version: 1.0.3 Pre-Alpha */
/* Created by UnSynk, tsesuv notsel */

#include "mkubf.h"

////////////////////////////////////////////////////////

bool version(void);
bool help(void);

////////////////////////////////////////////////////////

int main(int ac, char **av)
{	FILE *bmp;
	FILE *fnt;

	str ubfn = strset("font.ubf");

	uchar w = 8;
	uchar h = 16;

	uchar entries[4] = {0};

	uchar mode = 0;

	ubf *dat;

	for(unsigned int i = 0; i < ac; i++)
	{	if(strcmp(strset(av[i]), strset("/v")) || strcmp(strset(av[i]), strset("/version"))) return version();
		else if(strcmp(strset(av[i]), strset("/?")) || strcmp(strset(av[i]), strset("/help"))) return help();
		else if(strcmp(strset(av[i]), strset("/bmp")))
		{	bmp = fopen(av[i + 1], "rb");

			if(!bmp) return false;
		}
		else if(strcmp(strset(av[i]), strset("/ubf"))) ubfn = strset(av[i + 1]);
		else if(strcmp(strset(av[i]), strset("/width")))
		{	unsigned long int tmp = 0;
			for(unsigned int k = 0; k < strlen(strset(av[i + 1])); k++)
			{	tmp *= 10;
				tmp += av[i + 1][k] - '0';
			}
			w = tmp % 256;
		}
		else if(strcmp(strset(av[i]), strset("/height")))
		{	unsigned long int tmp = 0;
			for(unsigned int k = 0; k < strlen(strset(av[i + 1])); k++)
			{	tmp *= 10;
				tmp += av[i + 1][k] - '0';
			}
			h = tmp % 256;
		}
		else if(strcmp(strset(av[i]), strset("/entries")))
		{	unsigned long int tmp = 0;
			for(unsigned int k = 0; k < strlen(strset(av[i + 1])); k++)
			{	tmp *= 10;
				tmp += av[i + 1][k] - '0';
			}
			entries[0] = tmp % 256;
			entries[1] = (tmp >> 8) % 256;
			entries[2] = (tmp >> 16) % 256;
			entries[3] = (tmp >> 24) % 256;
		}
		else if(strcmp(strset(av[i]), strset("/mode")))
		{	unsigned long int tmp = 0;
			for(unsigned int k = 0; k < strlen(strset(av[i + 1])); k++)
			{	tmp *= 10;
				tmp += av[i + 1][k] - '0';
			}
			mode = tmp % 256;
		}
	}

	fnt = fopen(strget(ubfn), "wb");

	unsigned long int size =
		(
			mode == 0 ? (entries[0] + (entries[1] << 8) + (entries[2] << 16) + (entries[3] << 24) + 7) / 8 :
			mode == 1 ? (entries[0] + (entries[1] << 8) + (entries[2] << 16) + (entries[3] << 24) + 3) / 4 :
			mode == 2 ? (entries[0] + (entries[1] << 8) + (entries[2] << 16) + (entries[3] << 24) + 1) / 2 :
			mode == 3 ? (entries[0] + (entries[1] << 8) + (entries[2] << 16) + (entries[3] << 24)) :
			1
		) * w * h + sizeof(ubf);

	dat = (ubf *)malloc(size);

	sethead(dat, "UBF\0", 1, 0, 0, w, h, entries, mode);

	// BMPを読み込んでdatに追加する部分
	// BMPに関してはUBFにしやすい形式を作っちゃってそれを読み込むか

	fwrite(dat, 1, size, fnt);

	txoutln(strset("        Written report"));
	txoutln(strset("------------------------------"));
	txoutln(strset("Data (File) size: 0x%X (%d) Bytes\n"), size, size);
	txoutln(strset("======Header Information======"));
	txoutln(strset("	Signature: %s"), dat->Signature);
	txoutln(strset("	Version: %d.%d.%d"), dat->MajorV, dat->MinorV, dat->Patch);
	txoutln(strset("	Font Width: %d"), dat->Width);
	txoutln(strset("	Font Height: %d"), dat->Height);
	txoutln(strset("	Font Entries: %d"), dat->Entries[0] + (dat->Entries[1] << 8) + (dat->Entries[2] << 16) + (dat->Entries[3] << 24));
	txoutln(strset("	Font Mode: %d"), dat->Mode);
	txoutln(strset("========Data Infomation======="));
	txoutln(strset("	Entries data length (bit): %d"), dat->Width * dat->Height * (1 << dat->Mode));
	txoutln(strset("	Font Entries (Allocated): %d"), (size - sizeof(ubf)) * (mode == 0 ? 8 : mode == 1 ? 4 : mode == 2 ? 2 : 1) / (w * h));
	txoutln(strset("	Padding bits: %d"), ((size - sizeof(ubf)) * (mode == 0 ? 8 : mode == 1 ? 4 : mode == 2 ? 2 : 1) * (1 << dat->Mode)) - (dat->Width * dat->Height * (1 << dat->Mode) * (dat->Entries[0] + (dat->Entries[1] << 8) + (dat->Entries[2] << 16) + (dat->Entries[3] << 24))));
	txoutln(strset("------------------------------"));

	free(dat);

	fclose(bmp);
	fclose(fnt);

	return 0;
}

////////////////////////////////////////////////////////

bool version(void)
{	txoutln(strset("UnSynk Bmp Font Maker"));
	txoutln(strset("------------------------------"));
	txoutln(strset("Version: 1.0.3 Pre-Alpha"));
	txoutln(strset("Build: 2026021525"));
	txoutln(strset("------------------------------"));
	txoutln(strset("enter `MKUBF /?' you get more helps."));

	return true;
}

bool help(void)
{	txoutln(strset("UnSynk Bmp Font Maker"));
	txoutln(strset("------------------------------"));
	txoutln(strset("Usage:"));
	txoutln(strset("	MKUBF /bmp <filepath> </ubf <filename>> </w <width>> </h <height>> /entries <entries> </mode <mode>>"));
	txoutln(strset("------------------------------"));
	txoutln(strset("Options:"));
	txoutln(strset("	/bmp		:	Specifying the BMP file path."));
	txoutln(strset("	/ubf		:	Specifying the UBF file name (default: font.ubf)."));
	txoutln(strset("	/w		:	Specifying the font width (default: 8)."));
	txoutln(strset("	/h		:	Specifying the font height (default: 16)."));
	txoutln(strset("	/entries	:	Specifying the character set entries."));
	txoutln(strset("	/mode		:	Specifying the font mode (default: 0)."));
	txoutln(strset("	/?		:	Print this help message."));
	txoutln(strset("	/help		:	Print this help message."));
	txoutln(strset("	/v		:	Print software informations."));
	txoutln(strset("	/version	:	Print software informations."));

	return true;
}
