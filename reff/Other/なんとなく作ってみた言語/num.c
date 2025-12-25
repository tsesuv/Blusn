#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int trans(char *s);

int main(int ac, char **av)
{
	unsigned int a = trans(av[1]);
	printf("%d\n", a);

	return 0;
}

unsigned int trans(char *s)
{
	unsigned int v = 0;
	unsigned int maxsign = 0;
	unsigned int mspos = 0;

	for(int i = 0; i < strlen(s); i++)
	{
		switch(s[i])
		{
			case 'I':
				if(maxsign < 2)
				{
					maxsign = 1;
					mspos = i;
				}
				break;
			case 'V':
				if(maxsign < 4)
				{
					maxsign = 3;
					mspos = i;
				}
				break;
			case 'X':
				if(maxsign < 7)
				{
					maxsign = 6;
					mspos = i;
				}
				break;
			case 'K':
				if(maxsign < 37)
				{
					maxsign = 36;
					mspos = i;
				}
				break;
			case 'C':
				if(maxsign < 1297)
				{
					maxsign = 1296;
					mspos = i;
				}
				break;
			case 'H':
				break;
			case 'T':
				break;
			case 'S':
				break;
			case 'Z':
				break;
			case 'N':
				break;
			case 'Y':
				break;
			case 'U':
				break;
			case 'O':
				break;
			case 'L':
				break;
			case 'M':
				break;
			case 'G':
				break;
			case 'F':
				break;
			case 'R':
				break;
			case 'A':
				break;
			case 'P':
				break;
			case 'J':
				break;
			case 'W':
				break;
			case 'B':
				break;
			case 'E':
				break;
			case 'Q':
				break;
		}
	}

	for(int i = 0; i < mspos; i++)
	{}

	return v;
}
