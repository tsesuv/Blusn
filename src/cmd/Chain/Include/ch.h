#ifndef CH_H
#define CH_H

#include <stdio.h>
#include <stdint.h>

FILE *CMFILE;
char *Program = "";
uint32_t FILESIZE = 0;

struct
{
	int conj_op_dpr;
	int presrv_conj_op_dpr;
} var;

#endif /* ch.h */
