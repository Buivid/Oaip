#include <stdio.h>
#include <stdlib.h>
#include <time.h>

main()
{
	float array[100];
	int n, ind_neg, choice;

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
		while (scanf_s("%d", &n) != 1 || n < 1 || n>100|| getchar() != '\n')
		{
			printf("Error. Repeat\n");
			rewind(stdin);
		}
		system("cls");
		srand(time(NULL));
		for (int i = 0; i < n; i++)
			array[i] = rand() % 201 - 100;
		break;
	case 2:
		printf("Input number of elements\n");
		while (scanf_s("%d", &n) != 1 || n < 1|| n>100|| getchar() != '\n')
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
		system("cls");
		break;
	}
	for (int i = 0; i < n; i++)
		printf("%.2f  ", array[i]);
	printf("\nTo change the array, press any key\n");
	getch();
	for (int i = n - 1; i >= 0; i--)
	{
		if (array[i] < 0)
		{
			ind_neg = i;
			n++;
			for (int j = n - 1; j > ind_neg; j--)
				array[j] = array[j - 1];
		}
	}
	for (int i = 0; i < n; i++)
		printf("%.2f  ", array[i]);
	return 0;
}