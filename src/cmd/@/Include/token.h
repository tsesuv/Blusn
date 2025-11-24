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
	str dat;
	unsigned long int line;
	unsigned long int column;
} Token;

typedef struct tkList
{
	struct tkList *head;
	Token token;
	unsigned long int tk_cnt;
	unsigned long int cap;
	unsigned long int pos;
	struct tkList *next;
} tkList;

////////////////////////////////////////////////////////

Token tknnew(unsigned long int len);
Token tknclne(Token *t);
Token tknset(tkType type, str dat);
tkList *tklnew(unsigned long int cap);
tkList *tklgrow(void);
bool tklset(tkList *L, tkType type, const str dat, unsigned long int addPos);
tkList *tklclne(const tkList *t);

tkList *lexer(const str s);
tkList *parser(tkList *L);

////////////////////////////////////////////////////////

Token tknnew(unsigned long int len)
{
	Token t = *(Token *)malloc(sizeof(Token) * len);
	t.type = TK_VOID;
	t.dat = strnew(len);
	t.line = 0;
	t.column = 0;

	return t;
}

Token tknclne(Token *t)
{
	Token v = tknnew(strlen(t->dat));

	v.dat = strclne(&t->dat);
	v.line = t->line;
	v.column = t->column;

	return v;
}

Token tknset(tkType type, str dat)
{
	Token t = tknnew(strlen(dat));
	
	t.type = type;
	for(unsigned int i = 0; i < strlen(dat); i++) strpush(&t.dat, strget(dat)[i]);

	return t;
}

tkList *tklnew(unsigned long int tk_cnt)
{
	tkList *L = (tkList *)malloc(sizeof(tkList) * tk_cnt);
	L->head = L;
	L->token = tknset(TK_VOID, strset(""));
	L->tk_cnt = tk_cnt;
	L->cap = 1;
	L->pos = 0;
	L->next = NULL;

	return L;
}

tkList *tklgrow(void)
{
	tkList *new = tklnew(1);
	new->token = *(Token *)0;
	new->next = NULL;

	return new;
}

bool tklset(tkList *L, tkType type, const str dat, unsigned long int addPos)
{
	tkList *new = tklgrow();
	tkList *current = L->head;
	new->head = L->head;
	new->pos = addPos;
	new->token.type = type;
	new->token.dat = dat;

	while(current->pos != addPos - 1) current = current->next;
	new->next = current->next;
	current->next = new;
	while(current->next != NULL)
	{
		current->pos++;
		current = current->next;
	}

	return true;
}

bool tkldel(tkList *L)
{
	while(L->next->next != NULL) L = L->next;
	free(L->next);
	L->next = NULL;

	return true;
}

tkList *tklclne(const tkList *t)
{
	tkList *v = tklnew(t->tk_cnt);

	for(unsigned long int i = 0; i < t->tk_cnt; i++) v->token = tknclne(&t->token);
	v->head = t->head;
	v->tk_cnt = t->tk_cnt;
	v->cap = t->cap;
	v->pos = t->pos;

	return v;
}

tkList *lexer(const str s)
{
	tkList *L = tklnew(1);

	unsigned long int i = 0;
	str buf = strnew(64);
	while(strget(s)[i] != '\0')
	{
		if(strget(s)[i] == '\'')
		{
			while(strget(s)[i] != '\n' && strget(s)[i] != '\0') i++;
			i++;
			continue;
		} // 1行コメントスキップ
		if(strcmp(strsub(s, i, 3), strset(">>?")))
		{
			while(!strcmp(strsub(s, i, 3), strset("?<<"))) i++;
			i += 3;
			continue;
		} // 複数行コメントスキップ

		switch(strget(s)[i]) // トークンごとに分けたい
		{
			case '(':
				strpush(&buf, '\0');
				tklset(L, TK_LPAREN, buf, L->pos + 1);
				break;
			case ' ':
				strpush(&buf, '\0');
				if(strisdec(buf)) tklset(L, TK_NUM, buf, L->pos + 1);
				break;
			default:
				strpush(&buf, strget(s)[i]);
				break;
		}

		L->next = tklgrow();
		i++;
	}

	if(0 < strlen(s))
	{
		strpush(&buf, '\0');

		switch(strget(s)[i]) // トークンごとに分けたい
		{
			case '(':
				strpush(&buf, '\0');
				tklset(L, TK_LPAREN, buf, L->pos + 1);
				break;
			case ' ':
				strpush(&buf, '\0');
				if(strisdec(buf)) tklset(L, TK_NUM, buf, L->pos + 1);
				break;
			default:
				strpush(&buf, strget(s)[i]);
				break;
		}
	}
	else tkldel(L);

	return L;
}

tkList *parser(tkList *L)
{
	return 0;
}

////////////////////////////////////////////////////////

#endif
