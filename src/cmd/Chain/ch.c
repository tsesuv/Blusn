#include "ch.h"

int main(void)
{
	txoutln(strset("Hello, world!"));

	return 0;
}

/*
[DEF:MAIN:(
	OUT:'Hello, world!%j"'
)]
v
[DEF:MAIN:t]
v
t

[DEF:MAIN:(
	(LET:X:0)
	(IN:X)
	(IF:(GT:X:3):
		THEN:OUT:'$0 is Greater"':X
		:ELSE:OUT:'$0 is Smaller"':X
	)
)]
v
[DEF:MAIN:(
	(IN:X)
	(IF:(GT:X:3):
		THEN:OUT:'$0 is Greater"':X
		:ELSE:OUT:'$0 is Smaller"':X
	)
)]
v (X<-5)
[DEF:MAIN:(
	(IF:(GT:X:3):
		THEN:OUT:'$0 is Greater"':X
		:ELSE:OUT:'$0 is Smaller"':X
	)
)]
v
[DEF:MAIN:(
	(IF:t:
		THEN:OUT: '$0 is Greater"':X
		:ELSE:OUT: '$0 is Smaller"':X
	)
)]
v
[DEF:MAIN:(
	OUT:'$0 is Greater"':X
)]
v
[DEF:MAIN:t]
v
t
*/
