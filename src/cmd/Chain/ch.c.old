/* UnSynk Chain Interpreter */
/* Version: 1.2.0 Pre-Alpha */
/* Created by UnSynk, tsesuv notsel */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Include/ch.h"
#include "Include/token.h"

#include "Include/io.h"
#include "Include/type.h"

////////////////////////////////////////////////////////

int version()
{
	printf("=====UnSynk Chain Interpreter=====\n");
	printf(" Version: 1.2.0 Pre-Alpha\n");
	printf(" build: 2025101801\n");
	printf("----------------------------------\n");
	printf(" Created by UnSynk, tsesuv notsel\n");
	printf(" Enter 'ch /?` you get more helps.\n");
	exit(0);
}

int help()
{
	printf("UnSynk Chain Interpreter\n");
	printf("Usage:\n");
	printf("	ch [/i <chs file path>] [Options]\n");
	printf("Options:\n");
	printf("	/i Enter the chs file path.\n");
	printf("	/? This help message.\n");
	printf("	/v Print software informations.\n");
	exit(0);
}

int char2dec(char *p)
{
	int i = 0;
	int result = 0;
	while(p[i] != 0)
	{
		result *= 10;
		result += (int)p[i] - 0x30;
		i++;
	}
	return result;
}

int exec(char *p)
{
	return 0;
}

////////////////////////////////////////////////////////

int __firstinit(int argc, char **argv)
{
	if(argc < 2)
	{
		version();
	}

	for(int i = 0; i < argc; i++)
	{
		if(strcmp(*(argv + i), "/v") == 0)
		{
			version();
		}
		else if(strcmp(*(argv + i), "/?") == 0)
		{
			help();
		}
		else if(strcmp(*(argv + i), "/i") == 0)
		{
			CMFILE = fopen(*(argv + i + 1), "r");
		}
	}

	// int ReadFlag = 0;
	// while(ReadFlag > 0)
	// {
	// 	ReadFlag = fread(&Program[FILESIZE], sizeof(char), 1, CMFILE);
	// 	FILESIZE++;
	// }
	// fclose(CMFILE);
	// exec(Program);

	return 0;
}

char *_nomalize(const char *p)
{
	int memsize = strlen(p) * 4;
	char *result = malloc(memsize);
	int oidx = 0;
	char flag = 0;
	char ls_end_flag = 0;

	int i = 0;
	while(p[i] != '\0')
	{
		if(p[i] == '#')
		{
			while(p[i] != ';' && p[i] != '\n' && p[i] != '\0') i++;
			if(p[i] != '\0') i++;
			continue;
		}

		if(p[i] == '\'')
		{
			ls_end_flag++;
			if(flag) flag = 0;
			else
			{
				flag = 1;
				_append(result, &oidx, &memsize, "(LIST:");
			}
			i++;
		}
		else
		{
			if(memsize <= oidx)
			{
				memsize *= 2;
				result = realloc(result, memsize);
			}
			result[oidx] = p[i];
			
			if(flag)
			{
				if(p[i] == '%')
				{
					int bvalue = _pros_escape(p, i);
					char hex_str[4];
					sprintf(hex_str, "%d:", bvalue);
					_append(result, &oidx, &memsize, hex_str);
					i++;
				}
				else if(p[i] == '"')
				{
					_append(result, &oidx, &memsize, "0)");
				}
				else
				{
					char hex_str[4];
					sprintf(hex_str, "%d:", (uint8_t)p[i]);
					_append(result, &oidx, &memsize, hex_str);
				}
			}
			else
			{
				char hex_str[4];
				sprintf(hex_str, "%c", (uint8_t)p[i]);
				_append(result, &oidx, &memsize, hex_str);
				
			}

			i++;
		}
	}

	result[oidx] = '\0';

	return result;
}

tkList *_tokenalize(const char *p)
{
	tkList *tklist = malloc(sizeof(tkList));
	tklist->capacity = 64;
	tklist->tokens = malloc(sizeof(Token) * tklist->capacity);
	tklist->tk_count = 0;

	int i = 0;
	char buffer[1024];
	int bidx = 0;

	while(p[i] != '\0')
	{
		if(p[i] == '#')
		{
			while(p[i] != ';' && p[i] != '\n' && p[i] != '\0') i++;
			i++;
			continue;
		}

		if(p[i] == ':' || p[i] == '(' || p[i] == ')' || p[i] == '[' || p[i] == ']')
		{
			if(0 < bidx)
			{
				buffer[bidx] = '\0';
				_add_token(tklist, TK_SYM, buffer);
				bidx = 0;
			}

			_add_token(tklist, TK_OP, &p[i]);
		}
		else
		{
			buffer[bidx++] = p[i];
			i++;
		}

	}

	if(0 < bidx)
	{
		buffer[bidx] = '\0';
		_add_token(tklist, TK_SYM, buffer);
	}

	return tklist;
}

int _perse(const tkList *p)
{
	return 0;
}

////////////////////////////////////////////////////////

int print_tk(tkList *tklist)
{
	printf("Token count: %d\n", tklist->tk_count);

	for(int i = 0; i < tklist->tk_count; i++)
	{
		Token *t = &tklist->tokens[i];

		printf("[%d] ", i);
		
		if(t->type = TK_SYM) printf("SYMBOL: \"%s\"\n", t->value.symbol);
		else if(t->type = TK_OP)
		{
			switch(t->value.op)
			{
				case OP_COLON:
					printf("OP: :\n");
					break;
				case OP_PAREN_O:
					printf("OP: (\n");
					break;
				case OP_PAREN_C:
					printf("OP: )\n");
					break;
				case OP_BRACKET_O:
					printf("OP: [\n");
					break;
				case OP_BRACKET_C:
					printf("OP: ]\n");
					break;
			}
		}
	}
}

////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	__firstinit(argc, argv);
	getchar();

	char *nomalized = _nomalize("#test;[DEF:MAIN:(OUT:'Hello, world!%j\"')]\0");
	printf("Nomalized: %s\nLast char: %d\n", nomalized, nomalized[strlen(nomalized)]);
	getchar();

	tkList *tk_list = _tokenalize(nomalized);
	print_tk(tk_list);
	getchar();

	_perse(tk_list);

	return 0;
}
