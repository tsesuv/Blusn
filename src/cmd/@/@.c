/* UnSynk @ Compiler */
/* Version: 1.0.1 Pre-Alpha */
/* Created by UnSynk, tsesuv notsel */

#include <stdio.h>

#include "str.h"
#include "token.h"

////////////////////////////////////////////////////////

////////////////////////////////////////////////////////

int main(void)
{	str test = strset("Token1 >>? Hello ?<< Token2 123 000");
	txoutln(test);
	Token t = tknset(TK_STR, strset("Token2"));
	printf("Token: %d (type), %s\n", t.type, strget(t.dat));
	tknfree(&t);
	strfree(&test);

	return 0;
}

////////////////////////////////////////////////////////

bool version(void)
{	printf("      UnSynk @ Compiler\n");
	printf("------------------------------\n");
	printf(" Version: 1.0.1 Pre-Alpha\n");
	printf(" Build  : 2026020201\n");
	printf("------------------------------\n");
	printf("enter `@ /?' you get more helps.\n\n");

	return true;
}

bool help(void)
{	printf("      UnSynk @ Compiler\n");
	printf("------------------------------\n");
	printf("Usage:\n");
	printf("	@ </autoexit:{true|false}> </hidden:{true|false}> </delay:{true|false}> </src:[\\file\\path.@]\n");
	printf("------------------------------\n");
	printf("Options:\n");
	printf("	/autoexit	:	Enable auto exit flag.\n");
	printf("	/hidden		:	Enable output hidden flag.\n");
	printf("	/delay		:	Enable delay execute flag.\n");
	printf("	/src		:	Configuration source file path.\n");
	printf("	/?			:	Print this help message.\n");
	printf("	/help		:	Print this help message.\n");
	printf("	/h			:	Print this help message.\n");
	printf("	/v			:	Print software informations.\n");
	printf("	/version	:	Print software informations.\n");

	return true;
}

////////////////////////////////////////////////////////
