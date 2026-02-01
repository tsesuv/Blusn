#ifndef TOKEN_H
#define TOKEN_H

#include "ch.h"

typedef enum
{
	TK_OP,
	TK_SYM,
	TK_FMLA
} tkType;

typedef enum
{
	OP_COLON,
	OP_PAR_O,
	OP_PAR_C,
	OP_BLA_O,
	OP_BLA_C
} opType;

typedef struct
{
	tkType type;

	union
	{
		opType op;
		str symbol;
	} value;

	sint parPos;
} Token;

typedef struct
{
	Token *token;
	sint tkCount;
	sint cap;
} tkList;

#endif /* token.h */
