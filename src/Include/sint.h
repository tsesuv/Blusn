/* UnSynk SInt & Unsigned SInt Header */
/* Version: 1.0.0 Pre-alpha */
/* Created by UnSynk, tsesuv notsel */

#ifndef SINT_H
#define SINT_H

#include "type.h"

////////////////////////////////////////////////////////

sint sintnew(unsigned long int cap);

////////////////////////////////////////////////////////

sint sintnew(unsigned long int cap)
{
	sint v;
	v.vtype = VTYPE_SINT;
	v.dat = malloc(cap + 1);
	v.dat = 0;
	v.len = 0;

	return v;
}

bool sintfree(sint *v)
{
	return true;
}

#endif
