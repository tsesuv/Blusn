/* Lurt - Line Text Editor */
/* Build: 2026042621** */
/* Created by UnSynk, tsesuv notsel */

#include <stdio.h>
#include <stdlib.h>

typedef struct dat
{	char *line;
	struct dat *pr;
	struct dat *nx;
};

int main(int ac, char **av)
{	return 0;
}

dat datnew(void)
{	dat d;

	d.line = "";
	d.pr = NULL;
	d.nx = NULL;

	return d;
}

bool datfree(dat *d)
{	if(d->pr != NULL) return false;

	free(d->line);

	return true;
}
