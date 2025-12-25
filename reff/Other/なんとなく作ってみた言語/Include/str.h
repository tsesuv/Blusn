/* UnSynk String Header */
/* Version: 1.1.0 Pre-alpha */
/* Created by UnSynk, tsesuv notsel */

#ifndef STR_H
#define STR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

////////////////////////////////////////////////////////

#include "type.h"
#include "sint.h"

////////////////////////////////////////////////////////

str strnew(unsigned long int cap);
str strset(const char *p);

str strcat(const str s1, const str s2);
bool strpush(str *s, char c);
bool strrmv(str *s, unsigned long int pos);

str strsub(const str s, unsigned long int start, unsigned long int len);
bool strcmp(const str a, const str b);
str strclne(const str *s);

const unsigned long int strlen(const str s);
const char *strget(const str s);
bool strisdec(const str s);

sint str2sint(const str s);
usint str2usint(const str s);

str txin(void);
bool txout(const str s, ...);
bool txoutln(const str s, ...);

bool strfree(str *s);

////////////////////////////////////////////////////////

str strnew(unsigned long int cap)
{
	str s;

	s.vtype = VTYPE_STR;
	s.dat = malloc(cap + 1);
	s.dat[0] = '\0';
	s.len = 0;
	s.cap = cap;
	s.encode = 0;

	return s;
}

str strset(const char *p)
{
	unsigned long int len = 0;

	while(p[len]) len++;
	
	str s = strnew(len);

	for(int k = 0; k < len; k++) s.dat[k] = p[k];
	s.len = len;
	s.dat[s.len] = '\0';

	return s;
}

str strcat(const str s1, const str s2)
{
	str t = strclne(&s1);

	for(unsigned long int i = 0; i < s2.len; i++) strpush(&t, strget(s2)[i]);

	return t;
}

bool strpush(str *s, char c)
{
	if(!(s->len < s->cap))
	{
		s->cap = s->cap ? s->cap * 2 : 16;
		s->dat = realloc(s->dat, s->cap + 1);
	}

	s->dat[s->len++] = c;
	s->dat[s->len] = '\0';

	return true;
}

bool strrmv(str *s, unsigned long int pos)
{
	s->dat[pos] = '\0';
	s->len--;

	return true;
}

str strsub(const str s, unsigned long int start, unsigned long int len)
{
	if(s.len < start + len) len = s.len - start;

	str t = strnew(len);

	for(unsigned long int i = 0; i < len; i++) t.dat[i] = s.dat[start + i];
	t.len = len;
	t.dat[t.len] = '\0';

	return t;
}

bool strcmp(const str a, const str b)
{
	if(a.len != b.len) return false;

	for(unsigned long int i = 0; i < a.len; i++) if(a.dat[i] != b.dat[i]) return false;

	return true;
}

str strclne(const str *s)
{
	str t = strnew(s->len);

	for(unsigned long int i = 0; i < s->len; i++) t.dat[i] = s->dat[i];
	t.len = s->len;
	t.dat[t.len] = '\0';

	return t;
}

const unsigned long int strlen(str s)
{
	return s.len;
}

const char *strget(str s)
{
	return s.dat;
}

bool strisdec(str s)
{
	for(unsigned long int i = 0; i < strlen(s); i++)
	{
		for(unsigned long int k = 0; k < 10; k++) if(strget(s)[i] != (char)(k + 0x30)) return false;
	}

	return true;
}

sint str2sint(const str s)
{
	signed int a = 0;

	for(unsigned long int i = 0; i < strlen(s); i++)
	{
		a *= 10;
		a += strget(s)[i] - '0';
	}

	sint v = sintnew(a);

	return v;
}

usint str2usint(const str s)
{
	usint v = usintnew(0);

	return v;
}

str txin(void)
{
	str s = strnew(1);
	char *p;

	scanf("%s", p);
	s = strset(p);
	if(p[s.len] == '\n') strrmv(&s, s.len);

	return s;
}

bool txout(const str s, ...)
{
	va_list ap;
	va_start(ap, s);

	vprintf(s.dat, ap);

	va_end(ap);
	return true;
}

bool txoutln(const str s, ...)
{
	va_list ap;
	va_start(ap, s);

	strpush(&s, '\n');
	vprintf(s.dat, ap);

	va_end(ap);
	return true;
}

bool strfree(str *s)
{
	free(s->dat);
	s->dat = NULL;
	s->len = s->cap = 0;

	return true;
}

#endif
