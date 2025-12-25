/* UnSynk Packet Header */
/* Version: 1.0.0 Pre-alpha */
/* Created by UnSynk, tsesuv notsel */

#ifndef PACKET_H
#define PACKET_H

////////////////////////////////////////////////////////

#include "type.h"
#include "str.h"
#include "sint.h"

////////////////////////////////////////////////////////

packet pketnew(unsigned long int cap);

bool pketfree(packet *p);

////////////////////////////////////////////////////////

packet pketnew(unsigned long int cap)
{
	packet p;
	p.vtype = VTYPE_PACKET;
	p.key = strnew(cap);
	p.dat.vtype = VTYPE_ANY;
	p.dat.dat = NULL;
	p.used = false;
	p.addr = usintnew(0);
	p.next = usintnew(0);
	p.prev = usintnew(0);

	return p;
}

bool pketfree(packet *p)
{
	strfree(&p->key);
	usintfree(&p->addr);
	usintfree(&p->next);
	usintfree(&p->prev);
	p->dat.dat = NULL;
	p->used = false;

	return true;
}

#endif
