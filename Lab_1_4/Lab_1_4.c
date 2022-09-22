#include<stdio.h>
main()
{
	int n;
	printf("Input seasons number\n1.Winter\n2.Spring\n3.Summer\n4.Autumn\n");
	scanf_s("%d", &n);
	switch (n)
	{
	case 1:
		printf("December, January, February");
		break;
	case 2:
		printf("March, April, May");
		break;
	case 3:
		printf("June, July, August");
		break;
	case 4:
		printf("September, October, November");
		break;
	default:
		printf("Error");
	}
	return 0;
}