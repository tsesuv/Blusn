#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

////////////////////////////////////////////////////////

FILE *SrcFile;
FILE *ByteCode;

const char Header[] =
{
	0x58, 0x4D, 0x43, 0x00, 0x00, 0x02, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x55, 0x41, 0x43, 0x3A, 0x28,
	0x55, 0x6E, 0x53, 0x79, 0x6E, 0x6B, 0x20, 0x55,
	0x41, 0x43, 0x2D, 0x31, 0x2E, 0x30, 0x2E, 0x30,
	0x2D, 0x50, 0x41, 0x29, 0x20, 0x31, 0x2E, 0x30,
	0x2E, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00
};

int (* BuiltCmd)(int, ...);

////////////////////////////////////////////////////////

int version(int, ...);
int help(int, ...);
int write(const char *, const int *, const size_t, const size_t);

////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		version(0);
	}

	return 0;
}

int version(int l, ...)
{
	printf \
	( \
		"Blasn @ Compiler\n" \
		"-----------------\n" \
		"Version: 1.0.0 Pre-Alpha\n" \
		"Build  : 2025080804\n" \
		"-----------------\n" \
		"enter `@ /?' you get more helps.\n" \
	);
	exit(0);
}

int help(int l, ...)
{
	printf \
	( \
		"Blasn @ Compiler\n" \
		"-----------------\n" \
		"Usage:\n" \
		"\t@ src.@ </o:filename> </w>\n" \
		"-----------------\n" \
		"Options:" \
		"\t/o\t:\tSpecify output file name and file path.\n" \
		"\t/w\t:\tEnable additional warnings.\n" \
		"\t/?\t:\tPrint this help mesage.\n" \
	);
	exit(0);
}

int write(const char *file, const int *dat, const size_t dsize, const size_t dlngth)
{
	ByteCode = fopen(file, "wb");

	fwrite(dat, dsize, dlngth, ByteCode);

	fclose(ByteCode);

	return 0;
}
