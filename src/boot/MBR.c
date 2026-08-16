#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char chr;
typedef unsigned int uint;

chr print(chr *src)
{	chr ax = 0;

	while(1)
	{	ax = si++;

		if(!ax)
			break;

		putchar(ax);
	}

	return 0;
}

chr scmp(chr *src, chr *tar, chr cnt)
{	chr ax = 0;

	while(cnt)
	{	if(src[ax] == tar[ax])
			ax++;

		cnt--;
	}

	return ax;
}

int main(int ac, chr *av)
{	return 0;
}
