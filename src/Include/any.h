/* UnSynk Any Header */
/* Version: 1.0.0 Pre-alpha */
/* Created by UnSynk, tsesuv notsel */

#ifndef ANY_H
#define ANY_H

////////////////////////////////////////////////////////

#include "type.h"

////////////////////////////////////////////////////////

any anynew(void *dat, unsigned int dsize);

bool anyfree(any *a);

////////////////////////////////////////////////////////

any anynew(void *dat, unsigned int dsize)
{
	any a;

	a.vtype = VTYPE_ANY;
	a.dat = dat;
	a.dsize = dsize;
	
	return a;
}

bool anyfree(any *a)
{
	free(a->dat);
	a->dsize = 0;

	return true;
}

#endif
