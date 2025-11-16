/* UnSynk XMC Assembler */
/* Version: 1.1.4 Pre-Alpha */
/* Created by UnSynk, tsesuv notsel */

#include "xasm.h"
#include "str.h"

int main(void)
{
	str hi = strnew(1);
	hi = strset("Hello!\n");
	txout(&hi);

	strcat(&hi, strset("See you!\n"));
	txout(&hi);

	strfree(&hi);

	return 0;
}
