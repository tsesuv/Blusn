#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <conio.h>

////////////////////////////////////////////////////////

unsigned char BuiltInCmd[256][64] =
{
	"#exit", "#quit", "#bye", "#who"
};

char username[64] = "Chain live";

////////////////////////////////////////////////////////

int print(char *, ...);
int println(char *, ...);
int or(unsigned char *, unsigned char *);
int xor(unsigned char *, unsigned char *);

int b_exit(void);
int b_quit(void);
int b_bye(void);
int b_who(void);

////////////////////////////////////////////////////////

int main(void)
{
	unsigned int cc = 0;
	unsigned char c = 0;
	unsigned char cl[256] = {0};
	unsigned char flag = 0;
	while(1)
	{
		if(!(flag % 2))
		{
			print("C:: ");
			or(&flag, (unsigned char *)1);
		}

		c = getch();

		if(c != 0)
		{
			cl[cc] = c;
			cc++;
			c = 0;
		}

		for(int i = 0; i < strlen((char *)BuiltInCmd); i++)
		{
			if(strcmp((char *)cl, (char *)BuiltInCmd[i]) == 0)
			{
				switch(i)
				{
					case 0:
						b_exit();
						break;

					case 1:
						b_quit();
						break;

					case 2:
						b_bye();
						break;

					case 3:
						b_who();
						break;

					default:
						break;
				}

				for(int k = 0; k < 256; k++)
				{
					cl[k] = 0;
				}
				cc = 0;
				xor(&flag, (unsigned char *)1);
			}
		}
	}

	return 0;
}

////////////////////////////////////////////////////////

int b_exit(void)
{
	exit(0);
}

int b_quit(void)
{
	return b_exit();
}

int b_bye(void)
{
	return b_exit();
}

int b_who(void)
{
	println("%s@%s", "Chain REPL", username);
	return 0;
}

/* ----------vvv Utils vvv---------- */
int print(char *p, ...)
{
	va_list ap;
	va_start(ap, p);

	vprintf(p, ap);

	va_end(ap);

	return 0;
}

int println(char *p, ...)
{
	va_list ap;
	va_start(ap, p);
	
	vprintf(p, ap);
	
	va_end(ap);

	putchar(0x0D);
	putchar(0x0A);

	return 0;
}

int or(unsigned char *a, unsigned char *b)
{
	*a = *a || *b;
	return 0;
}

int and(unsigned char *a, unsigned char *b)
{
	*a = *a && *b;
	return 0;
}

int not(unsigned char *a)
{
	*a = !*a;
	return 0;
}

int xor(unsigned char *a, unsigned char *b)
{
	unsigned char *tmp = 0;
	*tmp = *a;
	or(tmp, b);
	and(a, b);
	not(a);
	and(tmp, a);
	*a = *tmp;
	return 0;
}
