#include <stdio.h>
#include <time.h>
#include <stdlib.h>

main()
{
	int n;
	int choice;
	float array[100];

	printf("Make a choice\n");
	printf("1.Random\n");
	printf("2.Hand input\n");
	while (scanf_s("%d", &choice) != 1 || choice < 1 || choice>2 || getchar()!='\n')
	{
		printf("Error. Repeat\n");
		rewind(stdin);
	}

	switch(choice)
	{
		case 1:
			printf("Input number of elements\n");
			while (scanf_s("%d", &n) != 1 || n < 1 || n > 100|| getchar() != '\n')
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
			while (scanf_s("%d", &n) != 1 || n < 1 || n > 100|| getchar() != '\n')
			{
				printf("Error. Repeat\n");
				rewind(stdin);
			}
			printf("Input elements\n");
			for (int i = 0; i < n; i++)
				while (scanf_s("%f", &array[i]) != 1)
				{
					printf("Error. Repeat\n");
					rewind(stdin);
				}
			break;
	}
	for (int i = 0; i < n; i++)
		printf("%.1f  ", array[i]);
	
	int ind_lost_pos, count=0;
	float sum = 0;

	for (int i = n - 1; i >= 0; i--)
	{
		if (array[i] > 0)
		{
			ind_lost_pos = i;
			count++;
			break;
		}
	}
	if (count == 1)
	{
		for (int i = 0; i < ind_lost_pos; i++)
			sum += array[i];
		printf("\nsum = %.2f", sum);
	}
	else
		printf("\nNot founded positive elements");
	return 0;
}