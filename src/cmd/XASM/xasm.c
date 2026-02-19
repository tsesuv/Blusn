/* UnSynk XMC Assembler */
/* Version: 1.0.0 */
/* Created by UnSynk, tsesuv notsel */

#include "map.h"

#include <stdio.h>

int main(void)
{	map m = mapnew(NULL);

	mapadd(&m, strset("test"), (void *)"value\0", 6);

	printf("%s\n", (char *)mapget(&m, strset("test")));

	mapfree(&m);

	return 0;
}
