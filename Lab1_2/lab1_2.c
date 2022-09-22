#include<stdio.h>
main()
{
	int k;
	printf("Input number\n");
	scanf_s("%d", &k);
	if (k % 2 == 0)
	{
		printf("Number is even");
	}
	else
	{
		printf("Number is not even");
	}
	return 0;
}