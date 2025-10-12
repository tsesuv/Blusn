#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

////////////////////////////////////////////////////////

FILE *SrcFile;
FILE *ByteCode;

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
		"UnSynk @ Compiler\n" \
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
		"UnSynk @ Compiler\n" \
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
