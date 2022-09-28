#include <stdio.h>
main()
{
	float a, b;
	int cnt = 0;
	printf(" Input A and B\n");
	scanf_s("%f%f", &a, &b);
	for (a; a >= b; a = a - b)
		cnt++;
	printf("Result = %d", cnt);
	return 0;
}