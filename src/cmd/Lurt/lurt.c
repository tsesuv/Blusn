/* UnSynk Lurt Line text editor */
/* Version: 1.0.0 Pre-alpha */
/* Created by UnSynk, tsesuv notsel */

/* 
   History
   2025/11/24/23:23: スクリーンエディタは諦めて新しいLurtとして開発開始
 */

#include "str.h"

////////////////////////////////////////////////////////

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

bool version(void)
{
	txoutln(strset("Lurt - A line editor trying respect EDLIN"));
	txoutln(strset("-----------------------------------------"));
	txoutln(strset(" Version: 1.0.0 Pre-Alpha"));
	txoutln(strset(" Build: 2025112401"));
	txoutln(strset("-----------------------------------------"));
	txoutln(strset("enter `LURT /?' you get more helps."));

	return true;
}

bool help(void)
{
	txoutln(strset("Lurt - A line editor trying respect EDLIN"));
	txoutln(strset("-----------------------------------------"));
	txoutln(strset("Usage:"));
	txoutln(strset("	LURT /I:<filepath> </B>"));
	txoutln(strset("-----------------------------------------"));
	txoutln(strset("Options:"));
	txoutln(strset("	/I	:	Specify file for edit."));
	txoutln(strset("	/B	:	Enable loading non last EOF."));
	txoutln(strset("	/?	:	Print this help message."));
	txoutln(strset("	/v	:	Print software informations."));

	return true;
}