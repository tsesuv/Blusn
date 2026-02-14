/* UnSynk Any Header */
/* Version: 1.0.2 Pre-Alpha */
/* Created by UnSynk, tsesuv notsel */

#ifndef ANY_H
#define ANY_H

////////////////////////////////////////////////////////

#include "type.h"

#include <stdlib.h>

////////////////////////////////////////////////////////

any anynew(void *dat, unsigned int dsize);

bool anyfree(any *a);

////////////////////////////////////////////////////////

any anynew(void *dat, unsigned int dsize)
{	any a;

	a.vtype = VTYPE_ANY;
	a.dat = malloc(dsize);

	unsigned char *s = (unsigned char *)dat;
	unsigned char *c = (unsigned char *)a.dat;

	for(unsigned int i = 0; i < dsize; i++) c[i] = s[i];

	a.dsize = dsize;

	return a;
}

bool anyfree(any *a)
{	free(a->dat);
	a->dsize = 0;

	return true;
}

////////////////////////////////////////////////////////

#endif /* any.h */
