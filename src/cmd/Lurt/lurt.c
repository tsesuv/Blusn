/* UnSynk Lurt Line text editor */
/* Version: 1.0.0 Pre-alpha */
/* Created by UnSynk, tsesuv notsel */

#include "str.h"

////////////////////////////////////////////////////////

FILE *text;

////////////////////////////////////////////////////////

bool edit(FILE *fp, str fname);

bool ChkFileExist(FILE *fp);
bool MakeNewFile(str fname);
bool ExecCmd(str cmd);

bool version(void);
bool help(void);

////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	if(argc < 2) exit(!version());

	for(int i = 0; i < argc; i++)
	{
		if(strcmp(strset(argv[i]), strset("/v"))) exit(!version());
		else if(strcmp(strset(argv[i]), strset("/?"))) exit(!help());
	}

	return 0;
}

////////////////////////////////////////////////////////

bool edit(FILE *fp, str fname)
{
	str cmd = strnew(1);

	if(ChkFileExist(fp)) txout(strset("New file"));

	txout(strset("*"));
	cmd = txin();

	ExecCmd(cmd);

	return true;
}

bool ChkFileExist(FILE *fp)
{
	return true;
}

bool MakeNewFile(str fname)
{
	return true;
}

bool ExecCmd(str cmd)
{
	return true;
}

bool version(void)
{
	txoutln(strset("Lurt - A line editor trying respect EDLIN"));
	txoutln(strset("-----------------------------------------"));
	txoutln(strset(" Version: 1.0.0 Pre-Alpha"));
	txoutln(strset(" Build: 2025112701"));
	txoutln(strset("-----------------------------------------"));
	txoutln(strset("enter `LURT /?' you get more helps."));

	return true;
}

bool help(void)
{
	txoutln(strset("Lurt - A line editor trying respect EDLIN"));
	txoutln(strset("-----------------------------------------"));
	txoutln(strset("Usage:"));
	txoutln(strset("	LURT /I:<filepath> </B> </E:{Encode}>"));
	txoutln(strset("-----------------------------------------"));
	txoutln(strset("Options:"));
	txoutln(strset("	/I	:	Specify file for edit."));
	txoutln(strset("	/B	:	Enable loading non last EOF."));
	txoutln(strset("	/E	:	Set file encode."));
	txoutln(strset("	/?	:	Print this help message."));
	txoutln(strset("	/v	:	Print software informations."));

	return true;
}