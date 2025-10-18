#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include "ch.h"

int _pros_escape(const char *p, int i)
{
	i++;

	switch(p[i])
	{
		case '0': return 0;
		case 'e': return 0x1B;
		case 'j': return 0x0A;
		case '6': break; // あとで対応する
		case '1': break;
		case '2': break;
		case '3': break;
		case '4': break;
		case '9': return 0x7F;
		default: return p[i];
	}
}

int _append(char *buffer, int *idx, int *memsize, const char *s)
{
	int l = strlen(s);
	while(*memsize <= *idx + l)
	{
		*memsize *= 2;
		buffer = realloc(buffer, *memsize);
	}

	strcpy(buffer + *idx, s);
	*idx += l;

	return 0;
}

////////////////////////////////////////////////////////

int _add_token(tkList *tklist, tkType type, const char *value)
{
	if(tklist->capacity <= tklist->tk_count)
	{
		tklist->capacity *= 2;
		tklist->tokens = realloc(tklist->tokens, sizeof(Token) * tklist->capacity);
	}

	Token *t = &tklist->tokens[tklist->tk_count];
	t->type = type;
	t->value.symbol = malloc(strlen(value) + 1);
	strcpy(t->value.symbol, value);

	tklist->tk_count++;

	return 0;
}

#endif /* token.h */
