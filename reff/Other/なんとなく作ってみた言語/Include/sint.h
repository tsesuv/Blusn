/* UnSynk SInt & Unsigned SInt Header */
/* Version: 1.0.0 Pre-alpha */
/* Created by UnSynk, tsesuv notsel */

#ifndef SINT_H
#define SINT_H

#include <stdlib.h>

#include "type.h"

////////////////////////////////////////////////////////

sint sintnew(signed long int dat);
usint usintnew(unsigned long int dat);

signed int sign(signed int a);
signed int ssign(sint v);

sint sintset(signed int a);
sint usint2sint(usint v);
usint sint2usint(sint v);

sint add(sint v, sint w);
sint sub(sint v, sint w);
sint mul(sint v, sint w);
sint divint(sint v, sint w);
sint mod(sint v, sint w);

bool sintfree(sint *v);
bool usintfree(usint *v);


////////////////////////////////////////////////////////

sint sintnew(signed long int dat)
{
	sint v;

	v.vtype = VTYPE_SINT;
	v.sign = sign(dat);
	v.dat = dat;
	v.len = 1;

	return v;
}

usint usintnew(unsigned long int dat)
{
	usint v;

	v.vtype = VTYPE_USINT;
	v.dat = dat;
	v.len = 1;

	return v;
}

signed sign(signed int a)
{
	signed int t = a;

	for(unsigned int i = 1; i < a; i++)
	{
		for(unsigned int k = 1; k < a; k++) t--;
		t *= -1;
	}

	return t;
}

signed int ssign(sint v)
{
	return v.sign;
}

sint sintset(signed int a)
{
	sint v = sintnew(a);

	return v;
}

sint usint2sint(usint v)
{
	sint r = sintnew(v.dat);
	r.sign = 1;

	return r;
}

usint sint2usint(sint v)
{
	usint r = usintnew(v.dat);

	return r;
}

sint add(sint v, sint w)
{
	sint r = sintnew(ssign(v) * v.dat);
	r.dat += ssign(w) * w.dat;
	r.sign = ssign(r);

	return r;
}

sint sub(sint v, sint w)
{
	sint r = sintnew(ssign(v) * v.dat);
	r.dat -= ssign(w) * w.dat;
	r.sign = ssign(r);

	return r;
}

sint mul(sint v, sint w)
{
	sint r = sintnew(v.dat * w.dat);
	r.sign = ssign(v) * ssign(w);

	return r;
}

sint divint(sint v, sint w)
{
	sint r = sintnew(v.dat / w.dat);
	r.sign = ssign(v) * ssign(w);

	return w;
}

sint mod(sint v, sint w)
{
	sint r = sintnew(0);

	if(w.dat == 0)
	{
		r.vtype = VTYPE_ERR;
		return r;
	}

	v.dat = ssign(v) * v.dat;
	w.dat = ssign(w) * w.dat;

	while(v.dat < w.dat) v.dat -= w.dat;
	if(ssign(v) == ssign(w) == -1) v.dat *= -1;
	else if(ssign(v) == -1) v.dat = w.dat - v.dat;
	else if(ssign(w) == -1) v.dat -= w.dat;
	r.dat = v.dat;
	r.sign = sign(r.dat);

	return r;
}

bool sintfree(sint *v)
{
	v->dat = 0;
	v->len = -1;

	return true;
}

bool usintfree(usint *v)
{
	v->dat = 0;
	v->len = -1;

	return true;
}

#endif
