/* UnSynk @ Compiler */
/* Version: 1.0.3 Pre-Alpha */
/* Created by UnSynk, tsesuv notsel */

#include "@.h"
#include "str.h"
#include "token.h"

////////////////////////////////////////////////////////

int main(void)
{	Token t = tknset(TK_STR, strset("Token2"));

	txoutln(strset("Token: %d (type), %s"), t.type, strget(t.dat));

	tkList *L = tklnew(NULL);
	tklset(L, t);
	tklset(L, tknset(TK_STR, strset("String")));

	L = L->head;
	txoutln(strset("Head: %s"), strget(L->token.dat));
	txoutln(strset("Next: %s"), strget(L->next->token.dat));
	txoutln(strset("Next: %s"), strget(L->next->next->token.dat));
	txoutln(strset(""));
	txoutln(strset("Head->end: %s"), strget(L->head->end->token.dat));

	tklfree(L);

	return 0;
}

////////////////////////////////////////////////////////

bool version(void)
{	txoutln(strset("      UnSynk @ Compiler"));
	txoutln(strset("------------------------------"));
	txoutln(strset(" Version: 1.0.3 Pre-Alpha"));
	txoutln(strset(" Build  : 2026020807"));
	txoutln(strset("------------------------------"));
	txoutln(strset("enter `@ /?' you get more helps.\n"));

	return true;
}

bool help(void)
{	txoutln(strset("      UnSynk @ Compiler"));
	txoutln(strset("------------------------------"));
	txoutln(strset("Usage:"));
	txoutln(strset("	@ </src:[\\file\\path.@]> </out:[\\file\\path]> </detail:{true|false}>"));
	txoutln(strset("------------------------------"));
	txoutln(strset("Options:"));
	txoutln(strset("	/src		:	Configuration source file path."));
	txoutln(strset("	/?			:	Print this help message."));
	txoutln(strset("	/help		:	Print this help message."));
	txoutln(strset("	/h			:	Print this help message."));
	txoutln(strset("	/v			:	Print software informations."));
	txoutln(strset("	/version	:	Print software informations."));

	return true;
}

////////////////////////////////////////////////////////
