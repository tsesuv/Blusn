#include "sint.h"
#include "str.h"

int main(void)
{
	txout(strset("Enter start dot: "));
	str start_s = txin();
	usint start_n = str2int(start_s);

	rgo(start_n);

	return 0;
}

usint rgo(usint n)
{
	if(mod(n, 2).dat && !(mod(sub(n, 1), 3)).dat) return divint(sub(n, 1), 3);
	else return mul(n, 2);
}
