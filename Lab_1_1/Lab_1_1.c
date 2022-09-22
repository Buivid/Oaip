#include<stdio.h>
main()
{
	float R, S, V;
	const double Pi = 3.14159;
	printf_s("Input Radius\nR = ");
	scanf_s("%f", &R);
	if (R > 0)
	{
		S = 4 * Pi * R * R;
		V = (4 * Pi * R * R * R) / 3;
		printf("S = %.2f\nV = %.2f", S, V);
	}
	else 
	{
		printf("Error");
	}
	return 0;
}