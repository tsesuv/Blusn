#ifndef CH_H
#define CH_H

#include <stdio.h>
#include "type.h"

FILE *CMFILE;
char *Program = "";
uint32_t FILESIZE = 0;

typedef enum
{
	TK_OP,
	TK_SYM,
	TK_FMLA
} tkType;

typedef enum
{
	OP_COLON,
	OP_PAREN_O,
	OP_PAREN_C,
	OP_BRACKET_O,
	OP_BRACKET_C
} opType;

typedef struct
{
	tkType type;

	union
	{
		opType op;
		char *symbol;
	} value;

	int char_pos;
	int opening_pos;
} Token;

typedef struct
{
	Token *tokens;
	int tk_count;
	int capacity;
} tkList;

#endif /* ch.h */
