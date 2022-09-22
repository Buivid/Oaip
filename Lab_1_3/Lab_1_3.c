#include <stdio.h>
int func(float a, float b)
{
	return a * b == 1.0f;
}
main()
{
	float a, b, c;
	int cnt = 0;
	printf("Input numbers a, b, c\n");
	scanf_s("%f%f%f", &a, &b, &c);
	cnt = func(a, b) + func(a, c) + func(b, c);
	printf("Result = %d", cnt);
	return 0;
}