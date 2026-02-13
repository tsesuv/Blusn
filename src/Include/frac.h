/* UnSynk Frac Header */
/* Version: 1.0.1 Pre-alpha */
/* Created by UnSynk, tsesuv notsel */

#ifndef FRAC_H
#define FRAC_H

////////////////////////////////////////////////////////

#include "type.h"
#include "sint.h"

////////////////////////////////////////////////////////

frac fracnew(sint denom, sint numer);

frac fracfree(frac *f);

////////////////////////////////////////////////////////

frac fracnew(sint denom, sint numer)
{	frac f;

	f.vtype = VTYPE_FRAC;
	f.sign = ssign(denom) * ssign(numer);
	f.denom = usintnew(ssign(denom) * denom.dat);
	f.numer = usintnew(ssign(numer) * numer.dat);

	return f;
}

#endif
