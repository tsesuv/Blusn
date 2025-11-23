/* UnSynk @ Evalizer */
/* Version: 1.0.0 Pre-Alpha */
/* Created by UnSynk, tsesuv notsel */

#include <stdio.h>

#include "str.h"

////////////////////////////////////////////////////////

int cmp(int a, int b);

////////////////////////////////////////////////////////

int main(void)
{
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
