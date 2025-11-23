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
	TK_VOID,
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

Token *tknnew(unsigned long int len);
Token *tknclne(Token *t);
Token *tknset(tkType type, str *value);
tkList *tklnew(unsigned long int cap);
tkList *tklclne(tkList *t);

tkList *lexer(str s);
tkList *parser(tkList *L);

bool addToken(tkList *tklist, tkType type, const str *value);

////////////////////////////////////////////////////////

Token *tknnew(unsigned long int len)
{
	Token *t = malloc(sizeof(Token) * len);
	t->type = TK_VOID;
	t->value = *(str *)NULL;

	return t;
}

Token *tknclne(Token *t)
{
	Token *v = tknnew(strlen(&t->value));

	for(int i = 0; i < strlen(&t->value); i++) strpush(&v->value, strget(&t->value)[i]);
}

Token *tknset(tkType type, str *value)
{
	Token *t = tknclne(tknnew(strlen(value)));
	
	t->type = type;
	for(unsigned int i = 0; i < strlen(value); i++) strpush(&t->value, strget(value)[i]);

	return t;
}

tkList *tklnew(unsigned long int cap)
{
	tkList *r;
	r->tokens = tknnew(cap);
	r->tk_cnt = 0;
	r->cap = sizeof(tkList) * cap;

	return r;
}

tkList *tklclne(tkList *t)
{
	tkList *v = tklnew(t->cap);

	for(int i = 0; i < t->tk_cnt; i++) v->tokens[i] = t->tokens[i];
	v->tk_cnt = t->tk_cnt;
	v->cap = t->cap;

	return v;
}

tkList *lexer(str s)
{
	tkList *tklist = tklclne(tklnew(64));

	unsigned long int i = 0;
	str buf = *strclne(strnew(64));
	while(strget(&s)[i] != '\0')
	{
		if(strget(&s)[i] == '\'')
		{
			while(strget(&s)[i] != '\n' && strget(&s)[i] != '\0') i++;
			i++;
			continue;
		} // 1行コメントスキップ
		if(strcmp(strsub(&s, i, 3), strset(">>?")))
		{
			while(!strcmp(strsub(&s, i, 3), strset("?<<"))) i++;
			i += 3;
			continue;
		} // 複数行コメントスキップ

		switch(strget(&s)[i]) // トークンごとに分けたい
		{
			case '(':
				strpush(&buf, '\0');
				addToken(tklist, TK_LPAREN, &buf);
				break;
			case ' ':
				strpush(&buf, '\0');
				if(strisdec(&buf)) addToken(tklist, TK_NUM, &buf);
				break;
			default:
				strpush(&buf, strget(&s)[i]);
				break;
		}
	}

	if(0 < strlen(&s))
	{
		strpush(&buf, '\0');

		switch(strget(&s)[i]) // トークンごとに分けたい
		{
			case '(':
				strpush(&buf, '\0');
				addToken(tklist, TK_LPAREN, &buf);
				break;
			case ' ':
				strpush(&buf, '\0');
				if(strisdec(&buf)) addToken(tklist, TK_NUM, &buf);
				break;
			default:
				strpush(&buf, strget(&s)[i]);
				break;
		}
	}

	return tklist;
}

tkList *parser(tkList *L)
{
	return 0;
}

////////////////////////////////////////////////////////

bool addToken(tkList *tklist, tkType type, const str *value)
{
	if(!(tklist->tk_cnt < tklist->cap))
	{
		tklist->cap *= 2;
		tklist->tokens = realloc(tklist->tokens, sizeof(Token) * tklist->cap);
	}

	Token *t = tknnew(strlen(value) + 1);
	tknset(type, value);

	tklist->tk_cnt++;

	return true;
}

#endif
