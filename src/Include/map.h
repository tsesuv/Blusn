/* UnSynk Map Header */
/* Version: 1.0.2 Pre-Alpha */
/* Created by UnSynk, tsesuv notsel */

#ifndef MAP_H
#define MAP_H

////////////////////////////////////////////////////////

#include "type.h"
#include "str.h"

#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////

////////////////////////////////////////////////////////

map mapnew(map *head)
{	map m;

	m.vtype = VTYPE_MAP;

	m.head = head == NULL ? &m : head;

	m.key = 0;
	m.dat = NULL;

	m.chld = &m;
	m.next = &m;

	m.cap = 0;
	m.len = 0;

	return m;
}

void *mapget(map *m, const str key)
{	map *o = m;
	unsigned long int i = 0;

	while(o->next != o)
	{	if(o->key == strget(key)[i])
		{	if(o->chld != o) o = o->chld;

			i++;
		} else o = o->next;
	}

	return o->dat;
}

////////////////////////////////////////////////////////

#endif /* map.h */
