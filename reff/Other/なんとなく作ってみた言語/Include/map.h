/* UnSynk Map Header */
/* Version: 1.0.0 Pre-alpha */
/* Created by UnSynk, tsesuv notsel */

#ifndef MAP_H
#define MAP_H

////////////////////////////////////////////////////////

#include "type.h"
#include "packet.h"

////////////////////////////////////////////////////////

map mapnew(unsigned long int cap);

bool mapfree(map *m);

////////////////////////////////////////////////////////

map mapnew(unsigned long int cap)
{
	map m;
	m.vtype = VTYPE_MAP;
	m.pool = pketnew(cap);
	m.cap = cap;
	m.len = 0;

	return m;
}

bool mapfree(map *m)
{
	pketfree(m->pool);
	m->len = m->cap = 0;

	return true;
}

#endif
