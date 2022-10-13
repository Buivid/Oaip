#include <stdio.h>
#include <stdlib.h>
#include <time.h>

main()
{
	int array1[100];
	int n_arr1;
	int array2[100]; 
	int n_arr2;
	int array3[100];
	int choice;
	printf("How you would input arrays\n");
	printf("1.Random input\n");
	printf("2.Hand input\n");
	while (scanf_s("%d", &choice) != 1 || choice != 1 && choice != 2|| getchar() != '\n')
	{
		printf("Error. Repeat\n");
		rewind(stdin);
	}

	switch (choice)
	{
	case 1:
		printf("Input number of elements in the first array\n");
		while (scanf_s("%d", &n_arr1) != 1 || n_arr1 < 1|| n_arr1>100|| getchar() != '\n')
		{
			printf("Error. Repeat\n");
			rewind(stdin);
		}
		srand(time(NULL));
		for (int i = 0; i < n_arr1; i++)
		{
			array1[i] = rand() % 201 - 100;
		}
		for (int i = 0; i < n_arr1; i++)
		{
			for (int j = 0; j < n_arr1 - i - 1; j++)
			{
				if (array1[j] > array1[j + 1])
				{
					int temp;
					temp = array1[j];
					array1[j] = array1[j + 1];
					array1[j + 1] = temp;
				}

			}
		}
		printf("Input number of elements in the second array\n");
		while (scanf_s("%d", &n_arr2) != 1 || n_arr2 < 1|| n_arr2>100|| getchar() != '\n')
		{
			printf("Error. Repeat");
			rewind(stdin);
		}
		srand(time(NULL));
		for (int i = 0; i < n_arr2; i++)
			array2[i] = rand() % 201 - 100;
		for (int i = 0; i < n_arr2; i++)
		{
			for (int j = 0; j < n_arr2 - i - 1; j++)
			{
				if (array2[j] < array2[j + 1])
				{
					int temp;
					temp = array2[j];
					array2[j] = array2[j + 1];
					array2[j + 1] = temp;
				}
			}
		}
		break;
	case 2:
		printf("Input number of elements in the first array\n");
		while (scanf_s("%d", &n_arr1) != 1 || n_arr1 < 1 || n_arr1>100|| getchar() != '\n')
		{
			printf("Error. Repeat\n");
			rewind(stdin);
		}
		printf("Input elements of array\n");
		for (int i = 0; i < n_arr1; i++)
		{
			while (scanf_s("%d", &array1[i]) != 1 || array1[i] <= array1[i - 1]|| getchar() != '\n')
			{
				printf("Error. Repeat\n");
				rewind(stdin);
			}
		}
		printf("Input number of elements in the second array\n");
		while (scanf_s("%d", &n_arr2) != 1 || n_arr2 < 1|| n_arr2>100|| getchar() != '\n')
		{
			printf("Error. Repeat\n");
			rewind(stdin);
		}
		printf("Input elements of array\n");
		for (int i = 0; i < n_arr2; i++)
		{
			while (scanf_s("%d", &array2[i]) != 1 || (i>0 && array2[i] >=  array2[i-1])|| getchar() != '\n')
			{
				printf("Error. Repeat\n");
				rewind(stdin);
			}
		}
		break;
	}
	for (int i = 0; i < n_arr1; i++)
		printf("%d ", array1[i]);
	printf("\n");
	for (int i = 0; i < n_arr2; i++)
		printf("%d ", array2[i]);
	printf("\n");
	int i = 0, j = n_arr2-1, k = 0;
	while (i < n_arr1 && j >=0)
	{
		if (array1[i] < array2[j])
		{
			array3[k] = array1[i];
			i++;
			k++;
		}
		else
		{
			array3[k] = array2[j];
			j--;
			k++;
		}
	}
	if (i == n_arr1)
	{
		for (; j >= 0; j--)
		{
			array3[k] = array2[j];
			k++;
		}
	}
	if (j < 0)
	{
		for (; i < n_arr1; i++)
		{
			array3[k] = array1[i];
			k++;
		}
	}

	printf("The third array\n");
	for (int i = 0; i < n_arr1+n_arr2 ; i++)
		printf("%d ", array3[i]);
	return 0;
}