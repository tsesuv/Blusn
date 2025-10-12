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
char *parce(char *p, char dchar, int i);
char *getstr(void);

typedef struct
{
	char *name;
	void *value;
	struct VarTable *next;
} VarTable;

char MARKER[5] = {0x00, 0x1B, 0x17, 0x03, 0x00};

VarTable *HashTable[TABLE_SIZE];

int SetVarData(const char *VarName, const void *VarData)
{
	uint32_t index = fnvla(VarName) % TABLE_SIZE;
	VarTable *OldVar = HashTable[index];
	while(OldVar != NULL)
	{
		if(strcmp(OldVar->name, VarName) == 0)
		{
			OldVar->value = (void *)VarData;
			return 0;
		}
		OldVar = (VarTable *)OldVar->next;
	}

	VarTable *Var = (VarTable *)malloc(sizeof(VarTable));
	Var->name = (char *)VarName;
	Var->value = (void *)VarData;
	Var->next = (struct VarTable *)HashTable[index];
	HashTable[index] = Var;
	return 0;
}

void *GetVarData(const char *VarName)
{
	uint32_t index = fnvla(VarName) % TABLE_SIZE;
	VarTable *Var = HashTable[index];
	while(Var != NULL)
	{
		if(strcmp(Var->name, VarName) == 0)
		{
			return Var->value;
		}
		Var = (VarTable *)Var->next;
	}
	return NULL;
}

int DelVarData(const char *VarName)
{
	uint32_t index = fnvla(VarName) % TABLE_SIZE;
	VarTable *Var = HashTable[index];
	while(Var != NULL)
	{
		if(strcmp(Var->name, VarName) == 0)
		{
			Var->name = NULL;
			Var->value = NULL;
			Var->next = NULL;
			return 0;
		}
		Var = (VarTable *)Var->next;
	}
	return 1;
}

char *parce(char *p, char dchar, int chank)
{
	int memsize = 1;
	char *res_list = (char *)malloc(sizeof(char *));
	if(!res_list)
	{
		free(res_list);
		return NULL;
	}

	int i = 0;
	int k = 0;
	int m = 0;
	while(*(p + i) != '\0')
	{
		if(memsize <= (m - 1))
		{
			char *tmp = (char *)realloc(res_list, sizeof(char *) * memsize);
			memsize++;
			if(!tmp)
			{
				return NULL;
			}
			res_list = tmp;
		}
		
		if((*(p + i) == dchar) && (*(p + i + 1) == dchar))
		{
			k++;
			i += 2;
		}
		else
		{
			if(k == chank)
			{
				*(res_list + m) = *(p + i);
				m++;
			}
			else if(chank < k)
			{
				*(res_list + m) = 0x00;
				return res_list;
			}
		}
		i++;
	}
	*(res_list + m) = 0x00;
	return res_list;
}

char *getstr(void)
{
	char c = 0;
	int length = 0;
	int memsize = 1;
	char *result = (char *)malloc(sizeof(char *));
	if(!result)
	{
		free(result);
		return NULL;
	}

	while(1)
	{
		if(memsize <= length)
		{
			memsize++;
			char *tmp = (char *)realloc(result, sizeof(char *) * memsize);
			if(!tmp)
			{
				free(result);
				return NULL;
			}
			result = tmp;
		}

		c = getchar();

		if((c == 0x0D) || (c == 0x0A))
		{
			break;
		}

		if((c == 0x08) && (0 < length))
		{
			length--;
			*(result + length) = 0x00;
		}
		else
		{
			*(result + length) = c;
			length++;
		}
	}

	if(length)
	{
		*(result + length) = 0x00;
		return result;
	}
	else
	{
		return MARKER;
	}
}

#endif
