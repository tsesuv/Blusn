/* UnSynk @ Compiler */
/* Version: 1.0.2 Pre-Alpha */
/* Created by UnSynk, tsesuv notsel */

#include "@.h"
#include "str.h"
#include "token.h"

////////////////////////////////////////////////////////

int main(void)
{	Token t = tknset(TK_STR, strset("Token2"));

	txoutln(true, strset("Token: %d (type), %s"), t.type, strget(t.dat));

	tknfree(&t);

	return 0;
}

////////////////////////////////////////////////////////

bool version(void)
{	txoutln(true, strset("      UnSynk @ Compiler"));
	txoutln(true, strset("------------------------------"));
	txoutln(true, strset(" Version: 1.0.2 Pre-Alpha"));
	txoutln(true, strset(" Build  : 2026020807"));
	txoutln(true, strset("------------------------------"));
	txoutln(true, strset("enter `@ /?' you get more helps.\n"));

	return true;
}

bool help(void)
{	txoutln(true, strset("      UnSynk @ Compiler"));
	txoutln(true, strset("------------------------------"));
	txoutln(true, strset("Usage:"));
	txoutln(true, strset("	@ </src:[\\file\\path.@]> </out:[\\file\\path]> </detail:{true|false}>"));
	txoutln(true, strset("------------------------------"));
	txoutln(true, strset("Options:"));
	txoutln(true, strset("	/src		:	Configuration source file path."));
	txoutln(true, strset("	/?			:	Print this help message."));
	txoutln(true, strset("	/help		:	Print this help message."));
	txoutln(true, strset("	/h			:	Print this help message."));
	txoutln(true, strset("	/v			:	Print software informations."));
	txoutln(true, strset("	/version	:	Print software informations."));

	return true;
}

////////////////////////////////////////////////////////
