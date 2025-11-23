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

typedef struct tkList
{
	Token *tokens;
	unsigned long int tk_cnt;
	struct tkList *next;
} tkList;

////////////////////////////////////////////////////////

Token tknnew(unsigned long int len);
Token tknclne(Token *t);
Token tknset(tkType type, str value);
tkList tklnew(unsigned long int cap);
tkList tklclne(const tkList *t);

tkList lexer(str s);
tkList *parser(tkList *L);

bool _addToken(tkList *L, tkType type, const str value);
bool _spritToken(char c, str *buf, tkList *L);

////////////////////////////////////////////////////////

// このファイルにおける一切の変更を禁ずる

Token tknnew(unsigned long int len)
{
	Token t = *(Token *)malloc(sizeof(Token) * len);
	t.type = TK_VOID;
	t.value = strnew(len);
	t.line = 0;
	t.column = 0;

	return t;
}

Token tknclne(Token *t)
{
	Token v = tknnew(strlen(t->value));

	v.value = strclne(&t->value);
	v.line = t->line;
	v.column = t->column;

	return v;
}

Token tknset(tkType type, str value)
{
	Token t = tknnew(strlen(value));
	
	t.type = type;
	for(unsigned int i = 0; i < strlen(value); i++) strpush(&t.value, strget(value)[i]);

	return t;
}

tkList tklnew(unsigned long int tk_cnt)
{
	tkList L;
	L.tokens[0] = tknnew(1);
	L.tk_cnt = 0;

	return L;
}

tkList tklclne(const tkList *t)
{
	tkList v = tklnew(t->tk_cnt);

	for(int i = 0; i < t->tk_cnt; i++) v.tokens[i] = tknclne(t->tokens);
	v.tk_cnt = t->tk_cnt;

	return v;
}

tkList lexer(const str s)
{
	tkList L = tklnew(64);

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

		_spritToken(strget(s)[i], &buf, &L);

		i++;
	}

	if(0 < strlen(s))
	{
		strpush(&buf, '\0');

		_spritToken(strget(s)[i], &buf, &L);
	}

	return L;
}

tkList *parser(tkList *L)
{
	return 0;
}

////////////////////////////////////////////////////////

bool _addToken(tkList *L, tkType type, const str value)
{
	Token t = tknnew(strlen(value) + 1);
	t = tknset(type, value);

	L->tk_cnt++;

	return true;
}

bool _spritToken(char c, str *buf, tkList *L)
{
	switch(c) // トークンごとに分けたい
	{
		case '(':
			strpush(buf, '\0');
			_addToken(L, TK_LPAREN, *buf);
			break;
		case ' ':
			strpush(buf, '\0');
			if(strisdec(*buf)) _addToken(L, TK_NUM, *buf);
			break;
		default:
			strpush(buf, c);
			break;
	}

	return true;
}

#endif
