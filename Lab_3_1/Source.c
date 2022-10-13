#include <stdio.h>
#include <stdlib.h>
#include <time.h>

main()
{
	float array[100];
	int n;
	int choice;

	printf("Make a choice\n");
	printf("1.Random input\n");
	printf("2.Hand input\n");
	while (scanf_s("%d", &choice) != 1 || choice < 1 || choice>2|| getchar() != '\n')
	{
		printf("Error. Repeat\n");
		rewind(stdin);
	}
	system("cls");

	switch (choice)
	{
	case 1:
		printf("Input number of elements\n");
		while (scanf_s("%d", &n) != 1 || n < 1|| n>100|| getchar() != '\n')
		{
			printf("Error. Repeat\n");
			rewind(stdin);
		}
		srand(time(NULL));
		for (int i = 0; i < n; i++)
			array[i] = rand() % 201 - 100;
		break;
	case 2:
		printf("Input number of elements\n");
		while (scanf_s("%d", &n) != 1 || n < 1|| getchar() != '\n')
		{
			printf("Error. Repeat\n");
			rewind(stdin);
		}
		printf("Input elements\n");
		for (int i = 0; i < n; i++)
		{
			while (scanf_s("%f", &array[i]) != 1|| getchar() != '\n')
			{
				printf("Error. Repeat\n");
				rewind(stdin);
			}
		}
		break;
	}
	system("cls");
	for (int i = 0; i < n; i++)
		printf("%.2f  ", array[i]);
	float max = array[0];
	for (int i = 0; i < n; i++)
	{
		if (array[i] > max)
			max = array[i];
	}
	printf("\nMax = %.2f", max);
	return 0;
}