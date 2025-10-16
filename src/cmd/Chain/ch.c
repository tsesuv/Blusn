/* UnSynk Chain Interpreter */
/* Version:1.1.0 Pre-Alpha */
/* Created by UnSynk, tsesuv notsel */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Include/io.h"
#include "Include/type.h"
#include "Include/ch.h"

////////////////////////////////////////////////////////

int version()
{
	printf("UnSynk Chain Interpreter Version:1.0.0 Pre-Alpha\r\n");
	printf("Created by UnSynk, tsesuv notsel\r\n");
	printf("Enter 'ch /?` you get more helps.\r\n");
	exit(0);
}

int help()
{
	printf("UnSynk Chain Interpreter\r\n");
	printf("Usage:\r\n");
	printf("	ch [/i <chs file path>] [Options]\r\n");
	printf("Options:\r\n");
	printf("	/i Enter the chs file path.\r\n");
	printf("	/? This help message.\r\n");
	printf("	/v Print software informations.\r\n");
	exit(0);
}

int char2dec(char *p)
{
	int i = 0;
	int result = 0;
	while(*(p + i) != 0)
	{
		result *= 10;
		result += (int)*(p + i) - 0x30;
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
	return "";
}

tkList *_tokenalize(const char *p)
{
	int i = 0;

	while(*(p + i) != '\0')
	{
		if(*(p + i) == '#')
		{
			while(*(p + i) != ';') i++;
			i++;
		}

		if(*(p + i) == '%')
		{
			i++;
			switch(*(p + i))
			{
				case 'j':
					putchar(0x0A);
					break;
			}
			i++;
		}

		printf("%c", *(p + i));

		i++;
	}

	return 0;
}

int _perse(const tkList *p)
{
	return 0;
}

////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	__firstinit(argc, argv);

	char *nomalized = _nomalize("#test;[DEF::MAIN::(OUT::'Hello, world!%j\"')]\0");

	tkList *tk_list = _tokenalize(nomalized);

	_perse(tk_list);

	return 0;
}
