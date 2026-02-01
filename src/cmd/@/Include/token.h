/* UnSynk Processing system Header */
/* Version: 1.0.1 Pre-alpha */
/* Created by UnSynk, tsesuv notsel */

#ifndef TOKEN_H
#define TOKEN_H

#include "str.h"

////////////////////////////////////////////////////////

typedef enum
{	TK_OP,
	TK_NEWL,
	TK_NUM,
	TK_STR,
	TK_IDEN,
	TK_KEYW,
	TK_LPAREN,
	TK_RPAREN,
	TK_LBRACKET,
	TK_RBRACKET,
	TK_COMMA,
	TK_COLON,
	TK_DOT,
	TK_AT,
	TK_VOID,
	TK_EOF
} tkType;

typedef struct
{	tkType type;
	str dat;
	unsigned long int line;
} Token;

typedef struct tkList
{	Token token;
	unsigned long int tkCnt;
	unsigned long int cap;
	unsigned long int pos;
	struct tkList *next;
} tkList;

////////////////////////////////////////////////////////

Token tknnew(unsigned long int len);
Token tknclne(Token *t);
Token tknset(tkType type, str dat);

tkList tklnew(unsigned long int len);

bool tknfree(Token *t);

tkList *tokenalizer(const str s);
tkList *parser(tkList *L);

////////////////////////////////////////////////////////

Token tknnew(unsigned long int len)
{	Token t;

	t.type = TK_VOID;
	t.dat = strnew(len);
	t.line = 0;

	return t;
}

Token tknclne(Token *t)
{	Token v = tknnew(strlen(t->dat));

	v.dat = strclne(&t->dat);
	v.line = t->line;

	return v;
}

Token tknset(tkType type, str dat)
{	Token t = tknnew(strlen(dat));

	t.type = type;
	for(unsigned int i = 0; i < strlen(dat); i++) strpush(&t.dat, strget(dat)[i]);

	return t;
}

tkList tklnew(unsigned long int len)
{	tkList L;

	L.token = tknnew(len);
	L.tkCnt = 0;
	L.cap = len;
	L.pos = 0;
	L.next = NULL;

	return L;
}

bool tknfree(Token *t)
{	strfree(&t->dat);
	t->line = 0;

	return true;
}

////////////////////////////////////////////////////////

#endif /* token.h */
