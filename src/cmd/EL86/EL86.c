#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

FILE *fp;
FILE *bak;

int b_exit(int crd, char *bname);
int cln(char *p);
int chkexist(char *path);
int prmpt(char *out);

int main(int ac, char **av)
{
	char *fname = (char *)malloc(sizeof(char));

	for(int i = 0; i < ac; i++)
	{
		if(strcmp(av[i], "/i") == 0)
		{
			fname = realloc(fname, strlen(av[i + 1]));
			strcpy(fname, av[i + 1]);
		}
	}
	char *bname = (char *)malloc(strlen(fname));
	strcpy(bname, fname);
	bname[strlen(bname) - 3] = 'B';
	bname[strlen(bname) - 2] = 'A';
	bname[strlen(bname) - 1] = 'K';

	char c = 0;
	fp = fopen(fname, "rb+");
	bak = fopen(bname, "wb");

	if(!fp)
	{
		fclose(fp);
		fp = NULL;
		return -1;
	}

	fclose(bak);



	char cmd[256] = {0};

	if(!chkexist(fname)) puts("New file");

	prmpt(cmd);
	if(strcmp(cmd, "q") == 0) b_exit(1, bname);
	cln(cmd);

	fclose(fp);

	free(bname);
	free(fname);
	bname = fname = NULL;

	return 0;
}

int b_exit(int crd, char *bname)
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

int cln(char *p)
{
	for(int i = 0; i < strlen(p); i++) p[i] = 0;

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
