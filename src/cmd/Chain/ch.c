#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

	int parPos;
} Token;

typedef struct
{
	Token *token;
	int tkCount;
	int cap;
} tkList;

int main(void)
{
	return 0;
}

/*
[DEF:MAIN:(
	OUT:'Hello, world!%j"'
)]

[DEF:MAIN:(
	(LET:X:0)
	(IN:X)
	(IF:(GT:X:3):
		THEN:OUT:'$0 is Greater"':X
		:ELSE:OUT:'$0 is Smaller"':X
	)
)]
*/
