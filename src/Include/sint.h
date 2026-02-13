/* UnSynk SInt & Unsigned SInt Header */
/* Version: 1.0.1 Pre-alpha */
/* Created by UnSynk, tsesuv notsel */

#ifndef SINT_H
#define SINT_H

////////////////////////////////////////////////////////

#include "type.h"

#include <stdlib.h>

////////////////////////////////////////////////////////

sint sintnew(signed long int dat);
usint usintnew(unsigned long int dat);

const signed int sign(const signed int a);
const signed int ssign(const sint v);

const sint sintset(const signed int a);
const sint usint2sint(const usint v);
const usint sint2usint(const sint v);

const sint add(const sint v, const sint w);
const sint sub(const sint v, const sint w);
const sint mul(const sint v, const sint w);
const sint divint(const sint v, const sint w);
const sint mod(const sint v, const sint w);

bool sintfree(sint *v);
bool usintfree(usint *v);

////////////////////////////////////////////////////////

sint sintnew(signed long int dat)
{	sint v;

	v.vtype = VTYPE_SINT;
	v.sign = sign(dat);
	v.dat = dat;
	v.len = 1;

	return v;
}

usint usintnew(unsigned long int dat)
{	usint v;

	v.vtype = VTYPE_USINT;
	v.dat = dat;
	v.len = 1;

	return v;
}

const signed int sign(const signed int a)
{	signed int t = a;

	for(unsigned int i = 1; i < a; i++)
	{	for(unsigned int k = 1; k < a; k++) t--;
		t *= -1;
	}

	return t;
}

const signed int ssign(const sint v)
{	return v.sign;
}

const sint sintset(const signed int a)
{	sint v = sintnew(a);

	return v;
}

const sint usint2sint(const usint v)
{	sint r = sintnew(v.dat);
	r.sign = 1;

	return r;
}

const usint sint2usint(const sint v)
{	usint r = usintnew(v.dat);

	return r;
}

const sint add(const sint v, const sint w)
{	sint r = sintnew(ssign(v) * v.dat);

	r.dat += ssign(w) * w.dat;
	r.sign = ssign(r);

	return r;
}

const sint sub(const sint v, const sint w)
{	sint r = sintnew(ssign(v) * v.dat);

	r.dat -= ssign(w) * w.dat;
	r.sign = ssign(r);

	return r;
}

const sint mul(const sint v, const sint w)
{	sint r = sintnew(v.dat * w.dat);

	r.sign = ssign(v) * ssign(w);

	return r;
}

const sint divint(const sint v, const sint w)
{	sint r = sintnew(v.dat / w.dat);

	r.sign = ssign(v) * ssign(w);

	return r;
}

const sint mod(const sint v, const sint w)
{	sint r = sintnew(0);

	if(w.dat == 0)
	{	r.vtype = VTYPE_ERR;
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
{	v->dat = 0;
	v->len = 0;

	return true;
}

bool usintfree(usint *v)
{	v->dat = 0;
	v->len = 0;

	return true;
}

////////////////////////////////////////////////////////

#endif /* sint.h */
