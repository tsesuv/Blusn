/* UnSynk Processing system Header */
/* Version: 1.0.0 Pre-alpha */
/* Created by UnSynk, tsesuv notsel */

#ifndef TOKEN_H
#define TOKEN_H

#include "str.h"

////////////////////////////////////////////////////////

typedef enum
{
	TK_OP,
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
	TK_AT_BEGIN,
	TK_AT_END,
	TK_EOF
} tkType;

typedef struct
{
	tkType type;
	str value;
	unsigned long int line;
	unsigned long int column;
} Token;

typedef struct
{
	Token *tokens;
	unsigned long int tk_cnt;
	unsigned long int cap;
} tkList;

////////////////////////////////////////////////////////

tkList *tklnew(unsigned long int cap);
tkList *tklclne(tkList *t);
Token *lexer(str s);
tkList *parce(tkList *L);

////////////////////////////////////////////////////////

tkList *tklnew(unsigned long int cap)
{
	tkList *r;
	r->tokens = malloc(sizeof(Token) * cap);
	r->tk_cnt = 0;
	r->cap = sizeof(tkList) * cap;

	return r;
}

tkList *tklclne(tkList *t)
{
	tkList *v = strnew(t->cap);

	for(int i = 0; i < t->tk_cnt; i++) v->tokens[i] = t->tokens[i];
	v->tk_cnt = t->tk_cnt;
	v->cap = t->cap;

	return v;
}

Token *lexer(str s)
{
	tkList *tklist = tklclne(tklnew(64));

	int i = 0;
	int bufi = 0;
	str buf = *strclne(strnew(64));
	while(strget(&s)[i] != '\0')
	{
		if(strget(&s)[i] == '\'')
		{
			while(strget(&s)[i] != '\n' && strget(&s)[i] != '\0') i++;
			i++;
			continue;
		}
	}

	return 0;
}

tkList *parce(tkList *L)
{
	return 0;
}

#endif
