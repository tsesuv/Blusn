/* UnSynk Map Header */
/* Version: 1.0.1 Pre-Alpha */
/* Created by UnSynk, tsesuv notsel */

#ifndef MAP_H
#define MAP_H

////////////////////////////////////////////////////////

#include "type.h"
#include "any.h"

////////////////////////////////////////////////////////

map mapnew(unsigned long int cap);

bool mapfree(map *m);

////////////////////////////////////////////////////////

map mapnew(unsigned long int cap)
{	map m;

	m.vtype = VTYPE_MAP;
	m.key = strnew(cap);
	m.dat = anynew(NULL, cap);
	m.cap = cap;
	m.len = 0;

	return m;
}

bool mapfree(map *m)
{	strfree(&m->key);
	anyfree(&m->dat);
	m->len = m->cap = 0;

	return true;
}

////////////////////////////////////////////////////////

#endif /* map.h */
