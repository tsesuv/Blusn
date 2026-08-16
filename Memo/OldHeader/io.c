#include "io.h"

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
