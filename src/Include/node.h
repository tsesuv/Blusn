/* UnSynk Node header */
/* Version: 1.0.0 Pre-Alpha */
/* Created by UnSynk, tsesuv notsel */

#ifndef NODE_H
#define NODE_H

////////////////////////////////////////////////////////

#include "type.h"
#include "str.h"

////////////////////////////////////////////////////////

node ndenew(node *head);

node ndeset(node *head, const str key, const void *dat, unsigned long int dsze, node *prev, node *next);

node ndeclne(node *n);

bool ndefree(node *n);

////////////////////////////////////////////////////////

node ndenew(node *head)
{	node n;

	n.vtype = VTYPE_NODE;

	n.head = head == NULL ? &n : head;

	n.key = strset("");
	n.dat = NULL;

	n.dsze = 0;

	n.prev = &n;
	n.next = &n;

	return n;
}

node ndeset(node *head, const str key, const void *dat, unsigned long int dsze, node *prev, node *next)
{	node n;

	n.vtype = VTYPE_NODE;

	n.head = head == NULL ? &n : head;

	n.key = key;
	n.dat = dat;

	n.dsze = dsze;

	n.prev = prev == NULL ? &n : prev;
	n.next = next == NULL ? &n : next;

	return n;
}

node ndeclne(node *n)
{	node q;

	q.vtype = VTYPE_NODE;

	q.head = n->head;

	q.key = strclne(&n->key);
	for(unsigned long int i = 0; i < n->dsze; i++) ((char *)q.dat)[i] = ((char *)n->dat)[i];
	q.dsze = n->dsze;

	q.prev = n->prev;
	q.next = n->next;

	return q;
}

bool ndefree(node *n)
{	n = n->head;
	node *t;

	while(n->next != n)
	{	t = n->next;

		strfree(&n->key);
		free(n->dat);

		n->key = strset("");
		n->dat = NULL;
		n->dsze = 0;

		n->prev = NULL;
		n->next = NULL;

		n = t;
	}

	return true;
}

////////////////////////////////////////////////////////

#endif /* node.h */
