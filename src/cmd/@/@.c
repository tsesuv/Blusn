/* UnSynk @ Evalizer */
/* Version: 1.0.0 Pre-Alpha */
/* Created by UnSynk, tsesuv notsel */

#include <stdio.h>

#include "str.h"
#include "token.h"

////////////////////////////////////////////////////////

int cmp(int a, int b);

////////////////////////////////////////////////////////

int main(void)
{
	str test = strset("Token1 Token2 123 000\n");
	txout(test);
	tkList *res = lexer(test);
	printf("Token list size: %d\n", res->tk_cnt);
	for(int i = 0; i < 4; i++)
	{
		printf("Token[%d]: %d (type), %s\n", i, res->token.type, strget(res->token.dat));
		res = res->next;
	}
	strfree(&test);

	return 0;
}

////////////////////////////////////////////////////////

bool version(void)
{
	printf("      UnSynk @ Evalizer\n");
	printf("------------------------------\n");
	printf(" Version: 1.0.0 Pre-Alpha\n");
	printf(" Build  : 2025112201\n");
	printf("------------------------------\n");
	printf("enter `@ /?' you get more helps.\n\n");

	return true;
}

bool help(void)
{
	printf("      UnSynk @ Evalizer\n");
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

int cmp(int a, int b)
{
	return a - b;
}
