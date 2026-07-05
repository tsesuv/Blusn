/* UnSynk @ language Token header */
/* Build: 20260530XXXX */
/* Created by UnSynk, tsesuv notsel */

#ifndef TOKEN_H
#define TOKEN_H

////////////////////////////////////////////////////////

#include "@.h"

////////////////////////////////////////////////////////

typedef enum
{	TK_VOID,
	TK_ENT,
	TK_IDR,
	TK_NME,
	TK_SYM,
	TK_STR,
	TK_NUM,
	TK_EOF
} tkType;

typedef struct
{	tkType type;
	byte *dat;
} Token;

typedef struct tkList
{	Token t;

	struct tkList *head;
	struct tkList *next;
} tkList;

////////////////////////////////////////////////////////

Token tknnew(void);
bit tknset(Token *t, tkType type, byte *d);

tkList *tklnew(tkList *head);
bit tklset(tkList *list, Token t);

bit tknfree(Token *t);
bit tklfree(tkList *list);

byte *type2str(tkType type);

////////////////////////////////////////////////////////

Token tknnew(void)
{	Token t;

	t.type = TK_VOID;
	t.dat = (byte *)malloc(sizeof(byte));

	return t;
}

bit tknset(Token *t, tkType type, byte *d)
{	bit x;

	t->type = type;
	free(t->dat);
	t->dat = (byte *)malloc(lenn(d) * sizeof(byte));

	byteset(t->dat, d, 0, 0, lenn(d));

	set(&x, 1);

	return x;
}

tkList *tklnew(tkList *head)
{	tkList *list = (tkList *)malloc(sizeof(tkList));

	list->head = head ? head : list;
	list->next = NULL;

	return list;
}

bit tklset(tkList *list, Token t)
{	bit x;
	tkList *ntkn = tklnew(list->head);

	ntkn->t = t;
	list->next = ntkn;

	set(&x, 1);

	return x;
}

bit tknfree(Token *t)
{	bit x;

	t->type = TK_VOID;
	free(t->dat);

	set(&x, 1);

	return x;
}

bit tklfree(tkList *list)
{	bit x;

	list = list->head;

	while(list)
	{	tkList *tmp = list->next;
		list->head = list->next = NULL;

		tknfree(&list->t);
		free(list);

		list = tmp;
	}

	set(&x, 1);

	return x;
}

byte *type2str(tkType type)
{	if(type == TK_VOID) return "TK_VOID";
	else if(type == TK_ENT) return "TK_ENT";
	else if(type == TK_IDR) return "TK_IDR";
	else if(type == TK_NME) return "TK_NME";
	else if(type == TK_SYM) return "TK_SYM";
	else if(type == TK_STR) return "TK_STR";
	else if(type == TK_NUM) return "TK_NUM";
	else if(type == TK_EOF) return "TK_EOF";

	return NULL;
}

////////////////////////////////////////////////////////

#endif /* token.h */
