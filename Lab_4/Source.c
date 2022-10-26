#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int hand_input_matrix(int size1, int size2, int matrica[100][100])
{
	system("cls");
	for (int i = 0; i < size1; i++)
	{
		printf("Input row number: %d\n", i + 1);
		for (int j = 0; j < size2; j++)
		{
			while (scanf_s("%d", &matrica[i][j]) != 1 || getchar() != '\n')
			{
				printf("Error. Repeat\n");
				rewind(stdin);
			}
		}
	}
}
int output_matrix(int size1, int size2, int matrica[100][100])
{
	for (int i = 0; i < size1; i++)
	{
		printf("\n");
		for (int j = 0; j < size2; j++)
			printf("%d ", matrica[i][j]);
	}
}
int random_input_matrix(int size1, int size2, int matrica[100][100])
{
	srand(time(NULL));
	for (int i = 0; i < size1; i++)
	{
		for (int j = 0; j < size2; j++)
			matrica[i][j] = rand() % 201 - 100;
	}
}
void main()
{
	int choice;
	printf("Choose the task\n");
	printf("1. The fist task\n");
	printf("2. The second task\n");
	printf("3. The third task\n");
	while (scanf_s("%d", &choice) != 1 || choice != 1 && choice != 2 && choice != 3 || getchar() != '\n')
	{
		printf("Error. Repeat\n");
		rewind(stdin);
	}
	system("cls");
	switch (choice)
	{
	case 1:
	{
		int matrix[100][100], col = 6, row = 6;
		int choice1, i, j;
		int min, max, sum = 0;
		printf("Make a choice\n");
		printf("1. Random input\n");
		printf("2. Hand input\n");
		while (scanf_s("%d", &choice1) != 1 || choice1 != 1 && choice1 != 2 || getchar() != '\n')
		{
			printf("Error. Repeat\n");
			rewind(stdin);
		}
		switch (choice1)
		{
		case 1:
			random_input_matrix(row, col, matrix);
			break;
		case 2:
			hand_input_matrix(row, col, matrix);
			break;
		}
		system("cls");
		for (i = 0; i < row; i++)
		{
			printf("\n");
			for (int j = 0; j < col; j++)
				printf("%d ", matrix[i][j]);
		}
		for (i = 0; i < row; i += 2)
		{
			min = matrix[i][0];
			for (j = 0; j < col; j++)
			{
				if (matrix[i][j] < min)
				{
					min = matrix[i][j];
				}
			}
			sum = sum + min;
		}
		for (i = 1; i < row; i += 2)
		{
			max = matrix[i][0];
			for (j = 0; j < col; j++)
			{
				if (matrix[i][j] > max)
				{
					max = matrix[i][j];
				}
			}
			sum = sum + max;
		}
		printf("\n\nResult = %d", sum);
		break;
	}
	case 2:
	{
		int choice2;
		int matrix[100][100], row, col;
		int i, j;
		int count = 0;
		printf("Make a choice\n");
		printf("1. Random input\n");
		printf("2. Hand input\n");
		while (scanf_s("%d", &choice2) != 1 || choice2 != 1 && choice2 != 2 || getchar() != '\n')
		{
			printf("Error. Repeat\n");
			rewind(stdin);
		}
		system("cls");
		switch (choice2)
		{
		case 1:
			printf("Input number of rows\n");
			while (scanf_s("%d", &row) != 1 || row < 1 || row>100 || getchar() != '\n')
			{
				printf("Error. Repeat\n");
				rewind(stdin);
			}
			printf("Input number of columns\n");
			while (scanf_s("%d", &col) != 1 || col < 1 || col>100 || getchar() != '\n')
			{
				printf("Error. Repeat\n");
				rewind(stdin);
			}
			random_input_matrix(row, col, matrix);
			break;
		case 2:
			printf("Input number of rows\n");
			while (scanf_s("%d", &row) != 1 || row < 1 || row>100 || getchar() != '\n')
			{
				printf("Error. Repeat\n");
				rewind(stdin);
			}
			printf("Input number of columns\n");
			while (scanf_s("%d", &col) != 1 || col < 1 || col>100 || getchar() != '\n')
			{
				printf("Error. Repeat\n");
				rewind(stdin);
			}
			hand_input_matrix(row, col, matrix);
			break;
		}
		system("cls");
		printf("Your matrix\n");
		output_matrix(row, col, matrix);
		for (i = 0; i < row; i++)
		{
			for (j = 1; j < col; j++)
			{
				if (matrix[i][j] <= matrix[i][j - 1])
					break;
				if (j == col-1)
				{
					for (int j = 0; j < (col/2); j++)
					{
						int temp = matrix[i][j];
						matrix[i][j] = matrix[i][col - j - 1];
						matrix[i][col - j -1] = temp;
					}
					printf("\n\nNew matrix\n");
					output_matrix(row, col, matrix);
					count++;
				}
			}
			if (count==1)
				break;
		}
		if (count == 0)
			printf("\n\nThe matrix has not changed\n");
		break;
	}
	case 3:
	{
		int matrix[100][100], size;
		int choice3;
		int sum=0;
		int i, j;
		printf("Menu\n");
		printf("1. Random input\n");
		printf("2. Hand input\n");
		while (scanf_s("%d", &choice3) != 1 || choice3 != 1 && choice3 != 2 || getchar() != '\n')
		{
			printf("Error. Repeat\n");
			rewind(stdin);
		}
		system("cls");
		switch (choice3)
		{
		case 1:
			printf("Input size of matrix\n");
			while (scanf_s("%d", &size) != 1 || size <= 0 || size > 100 || getchar() != '\n')
			{
				printf("Error. Repeat\n");
				rewind(stdin);
			}
			random_input_matrix(size, size, matrix);
			break;
		case 2:
			printf("Input size of matrix\n");
			while (scanf_s("%d", &size) != 1 || size <= 0 || size > 100 || getchar() != '\n')
			{
				printf("Error. Repeat\n");
				rewind(stdin);
			}
			hand_input_matrix(size, size, matrix);
			break;
		}
		system("cls");
		printf("Your matrix\n");
		for (i = 0; i < size; i++)
		{
			printf("\n");
			for (j = 0; j < size; j++)
				printf("%d ", matrix[i][j]);
		}
		int begin = 0, finish = size - 1;
		for (i = size-1; i >= (size/2); i--)
		{
			for(j = begin; j <= finish; j++)
				sum += matrix[i][j];
			begin++;
			finish--;
		}
		printf("\n\nSumma = %d", sum);
		break;
	}
	}
}
