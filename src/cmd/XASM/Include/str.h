/* UnSynk String Header */
/* Version: 1.0.2 Pre-alpha */
/* Created by UnSynk, tsesuv notsel */

#ifndef STR_H
#define STR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

////////////////////////////////////////////////////////

typedef enum {false, true} bool;

typedef struct
{
	char *dat; // data
	unsigned long int len; // 長さ
	int cap; // キャパシティ
	int ecnum; // 文字エンコードも保持したいよなぁ。0でASCII、とか。やり方わからんがな。
} str;

////////////////////////////////////////////////////////

str strnew(int cap);
str strset(const char *p);
bool strcat(str *s1, str s2);
bool strpush(str *s, char c);
bool txout(const str *fmt, ...);
str strsub(const str s, unsigned long int start, unsigned long int len);
bool strcmp(const str a, const str b);
str strclne(const str *s);
const unsigned long int strlen(str s);
const char *strget(str s);
bool strfree(str *s);

////////////////////////////////////////////////////////

str strnew(int cap)
{
	str s;
	s.dat = malloc(cap + 1);
	s.dat[0] = '\0';
	s.len = 0;
	s.cap = cap;
	s.ecnum = 0;

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

bool strcat(str *s1, str s2)
{
	str t = strnew(s2.len);
	t = strclne(&s2);
	for(int i = 0; i < t.len; i++) strpush(s1, t.dat[i]);

	strfree(&t);
	return true;
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

bool txout(const str *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);

	vprintf(fmt->dat, ap);

	va_end(ap);

	return true;
}

str strsub(const str s, unsigned long int start, unsigned long int len)
{
	if(s.len < start + len) len = s.len - start;
	str t = strnew(len);

	for(int i = 0; i < len; i++)
	{
		t.dat[i] = s.dat[start + i];
	}
	t.len = len;
	t.dat[t.len] = '\0';

	return t;
}

bool strcmp(const str a, const str b)
{
	if(a.len != b.len) return false;

	for(int i = 0; i < a.len; i++)
	{
		if(a.dat[i] != b.dat[i]) return false;
	}

	return true;
}

str strclne(const str *s)
{
	str t = strnew(s->len);

	for(int i = 0; i < s->len; i++) t.dat[i] = s->dat[i];
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

bool strfree(str *s)
{
	free(s->dat);
	s->dat = NULL;
	s->len = s->cap = 0;

	return true;
}

#endif
