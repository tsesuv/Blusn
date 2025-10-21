/* UnSynk I/O header */
/* Version:1.3.1 Pre-Alpha */

#ifndef IO_H
#define IO_H

#define TABLE_SIZE 65536

#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include "hash.h"

int SetVarData(const char *VarName, const void *VarData);
void *GetVarData(const char *VarName);
int DelVarData(const char *VarName);
char *getstr(void);

typedef struct
{
	char *name;
	void *value;
	struct VarTable *next;
} VarTable;

char MARKER[5] = {0x00, 0x1B, 0x17, 0x03, 0x00};

VarTable *HashTable[TABLE_SIZE];

#endif
