/* UnSynk Map Header */
/* Version: 1.0.2 Pre-Alpha */
/* Created by UnSynk, tsesuv notsel */

#ifndef MAP_H
#define MAP_H

////////////////////////////////////////////////////////

#include "type.h"
#include "node.h"

#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////

map *mapnew(node *head);

bool mapadd(map *m, node n);

void *mapget(map *m, const str key);

bool mapfree(map *m);

////////////////////////////////////////////////////////

map *mapnew(node *head)
{	map *m = (map *)malloc(sizeof(map));

	m->vtype = VTYPE_MAP;

	node n = ndeset(NULL, strset(""), NULL, 0, NULL, NULL);
	m->tree = &n;

	m->cap = 0;
	m->len = 0;

	return m;
}

bool mapadd(map *m, node n)
{	m->tree = &n;

	return true;
}

void *mapget(map *m, const str key)
{	map *o = m;
	unsigned long int i = 0;

	while(o->tree->next != o->tree)
	{	if(strget(o->tree->key)[i] == strget(key)[i])
		{	if(o->chld != o) o = o->chld;

			i++;
		} else o->tree = o->tree->next;
	}

	return o->tree->dat;
}

bool mapfree(map *m)
{	node *n = m->tree->head;
	map *t = m;
	unsigned long int i = 0;

	txoutln(strset("F0"));

	do
	{	m = m->chld;
		i++;
		txoutln(strset("F1"));
	} while(m->chld != m);

	for(unsigned long int k = 0; k < i; k++)
	{	for(unsigned long int n = 0; n < i - k; n++) m = m->chld;
		do
		{	t->tree = m->tree->next;
			txoutln(strset("F2"));
			if(m->len) ndefree(m->tree);
			free(m);
			m = t;
		} while(m->tree->next != m->tree);
		txoutln(strset("F3"));
	}

	return true;
}

////////////////////////////////////////////////////////

#endif /* map.h */
