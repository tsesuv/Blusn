/* UnSynk String Header */
/* Version: 1.1.2 Pre-alpha */
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
str strset(char *p);

str strcat(str s1, str s2);
bool strpush(str *s, char c);
bool strrmv(str *s, unsigned long int pos);

str strsub(str s, unsigned long int start, unsigned long int len);
bool strcmp(str a, str b);
str strclne(str *s);

unsigned long int strlen(str s);
char *strget(str s);
bool strisdec(str s);

sint str2sint(str s);
usint str2usint(str s);

str txin(void);
bool txout(bool isImm, str s, ...);
bool txoutln(bool isImm, str s, ...);

bool strfree(str *s);

////////////////////////////////////////////////////////

str strnew(unsigned long int cap)
{	str s;

	s.vtype = VTYPE_STR;
	s.dat = (char *)malloc(cap + 1);
	s.dat[0] = '\0';
	s.len = 0;
	s.cap = cap;
	s.encode = 0;

	return s;
}

str strset(char *p)
{
	unsigned long int len = 0;

	while(p[len]) len++;

	str s = strnew(len);

	for(int k = 0; k < len; k++) s.dat[k] = p[k];
	s.len = len;
	s.dat[s.len] = '\0';

	return s;
}

str strcat(str s1, str s2)
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
		s->dat = (char *)realloc(s->dat, s->cap + 1);
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

str strsub(str s, unsigned long int start, unsigned long int len)
{
	if(s.len < start + len) len = s.len - start;

	str t = strnew(len);

	for(unsigned long int i = 0; i < len; i++) t.dat[i] = s.dat[start + i];
	t.len = len;
	t.dat[t.len] = '\0';

	return t;
}

bool strcmp(str a, str b)
{
	if(a.len != b.len) return false;

	for(unsigned long int i = 0; i < a.len; i++) if(a.dat[i] != b.dat[i]) return false;

	return true;
}

str strclne(str *s)
{
	str t = strnew(s->len);

	for(unsigned long int i = 0; i < s->len; i++) t.dat[i] = s->dat[i];
	t.len = s->len;
	t.dat[t.len] = '\0';

	return t;
}

unsigned long int strlen(str s)
{
	return s.len;
}

char *strget(str s)
{
	return s.dat;
}

bool strisdec(str s)
{	bool ls[10] = {true};
	bool t = false;
	for(unsigned long int i = 0; i < strlen(s); i++) if(strget(s)[i] < '0' || '9' < strget(s)[i]) return false;

	return true;
}

sint str2sint(str s)
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

usint str2usint(str s)
{
	usint v = usintnew(0);

	return v;
}

str txin(void)
{
	str s = strnew(0);
	int c;

	while((c = getchar()) != '\n' && c != EOF) strpush(&s, c);

	return s;
}

bool txout(bool isImm, str s, ...)
{
	va_list ap;
	va_start(ap, s);

	vprintf(s.dat, ap);

	va_end(ap);
	if(isImm) strfree(&s);
	return true;
}

bool txoutln(bool isImm, str s, ...)
{
	va_list ap;
	va_start(ap, s);

	vprintf(s.dat, ap);
	printf("\n");

	va_end(ap);
	if(isImm) strfree(&s);
	return true;
}

bool strfree(str *s)
{
	free(s->dat);
	s->dat = NULL;
	s->len = s->cap = 0;

	return true;
}

#endif /* str.h */
