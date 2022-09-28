#include <stdio.h>
main()
{
	int i = 1626;
	double res = 20;
	for (i; i <= 2022; i++)
		res = 1.04 * res;
	printf("Price of island today = %f", res);
	return 0;
}