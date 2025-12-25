/* UnSynk EL32 Line text editor */
/* Version: 1.0.0 Pre-alpha */
/* Created by UnSynk, tsesuv notsel */

#include <fcntl.h>
#include <unistd.h>

#include "type.h"
#include "str.h"
#include "map.h"

////////////////////////////////////////////////////////

FILE *text;

////////////////////////////////////////////////////////

bool edit(FILE *fp, str fname);

bool ChkFileExist(FILE *fp, str fname);
bool OpenFile(FILE *fp, str fname);
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
	bool FileState[5] = {false, false, false, false, false}; // FileIsNew, General error, ReadOnly error, NoRoom error

	FileState[0] = ChkFileExist(fp, fname);
	FileState[1] = OpenFile(fp, fname);
	
	for(unsigned int i = 1; i < 5; i++)
	{
		if(!FileState[i])
		{
			switch(i)
			{
				case 1:
					txoutln(strset("File Creation Error"));
					break;
				case 2:
					txoutln(strset("File is READ-ONRY"));
					break;
				case 3:
					txoutln(strset("No room in directory for file"));
					break;
				case 4:
					txoutln(strset("Unknown file state (4)"));
					break;
				case 5:
					txoutln(strset("Unknown file state (5)"));
					break;
			}
		}
	}
	if(FileState[0]) txoutln(strset("New file"));

	txout(strset("*"));
	cmd = txin();

	ExecCmd(cmd);

	return true;
}

bool ChkFileExist(FILE *fp, str fname)
{
	int NewFMode = -1;
	int fd = open(strget(fname), O_CREAT | O_EXCL | O_WRONLY, NewFMode);

	return fd != -1 ? true :  false;
}

bool OpenFile(FILE *fp, str fname)
{
	errno res = {1, fopen_s(&fp, strget(fname), "w")};

	return res.code == 0 ? true : false;
}

bool ExecCmd(str cmd)
{
	return true;
}

bool version(void)
{
	txoutln(strset("EL32 - A line editor trying respect EDLIN"));
	txoutln(strset("-----------------------------------------"));
	txoutln(strset(" Version: 1.0.0 Pre-Alpha"));
	txoutln(strset(" Build: 2025122501"));
	txoutln(strset("-----------------------------------------"));
	txoutln(strset("enter `EL32 /?' you get more helps."));

	return true;
}

bool help(void)
{
	txoutln(strset("EL32 - A line editor trying respect EDLIN"));
	txoutln(strset("-----------------------------------------"));
	txoutln(strset("Usage:"));
	txoutln(strset("	EL32 /I:<filepath> </B> </E:{Encode}>"));
	txoutln(strset("-----------------------------------------"));
	txoutln(strset("Options:"));
	txoutln(strset("	/I	:	Specify file for edit."));
	txoutln(strset("	/B	:	Enable loading non last EOF."));
	txoutln(strset("	/E	:	Set file encode."));
	txoutln(strset("	/?	:	Print this help message."));
	txoutln(strset("	/v	:	Print software informations."));

	return true;
}