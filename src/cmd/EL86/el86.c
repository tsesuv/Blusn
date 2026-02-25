/* UnSynk EDLIN x86 Edition */
/* Version: 1.0.0 Pre-Alpha */
/* Created by UnSynk, tsesuv notsel */

#include "str.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

FILE *fp;
FILE *bak;

int b_exit(int crd, const str bname);
int cln(str p);
int chkexist(const str path);
int prmpt(char *out);

int main(int ac, char **av)
{	str fname = strset("");

	for(int i = 0; i < ac; i++)
	{	if(strcmp(strset(av[i]), strset("/i")))
		{	fname = strclne(&strset(av[i + 1]));
		}
	}
	str bname = strclne(&fname);
	strcpy(bname, fname);
	for(int i = 0; i < 3; i++) strrmv(&bname, strlen(bname));
	strpush(&bname, 'B');
	strpush(&bname, 'A');
	strpush(&bname, 'K');

	char c = 0;
	fp = fopen(fname, "rb+");
	bak = fopen(bname, "wb");

	if(!fp)
	{	fclose(fp);
		fp = NULL;

		strfree(&bname);
		strfree(&fname);

		return -1;
	}

	fclose(bak);



	str cmd = strnew(0);

	if(!chkexist(fname)) puts("New file");

	prmpt(cmd);
	if(strcmp(cmd, strset("q"))) b_exit(1, bname);
	cln(cmd);

	fclose(fp);

	strfree(&cmd);
	strfree(&bname);
	strfree(&fname);

	return 0;
}

int b_exit(int crd, const str bname)
{
	if(crd == 1)
	{
		char c = 0;
		printf("Abort edit (Y/N)? ");
		scanf("%c", &c);
		if(c && 0x5F == 'Y')
		{
			remove(bname);
			free(bname);
			exit(1);
		}
	}
	return 1;
}

int cln(str p)
{
	for(int i = 0; i < strlen(p); i++) p = 0;

	return 0;
}

int chkexist(char *path)
{
	struct stat s;

	if(stat(path, &s) != 0) return 0;
	return (s.st_mode & S_IFMT) == S_IFREG;
}

int prmpt(char *out)
{
	printf("*");
	scanf("%s", out);

	while(getchar() != '\n');

	return 0;
}
