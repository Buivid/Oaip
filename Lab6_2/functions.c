#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void check_input(int* choice)
{
	while (scanf_s("%d", choice) != 1 || (*choice != 1 && *choice != 2) || getchar() != '\n')
	{
		printf("Error\n");
		rewind(stdin);
	}
}
void check_size(int* size)
{
	while (scanf_s("%d", size) != 1 || *size < 1 || getchar() != '\n')
	{
		printf("Error\n");
		rewind(stdin);
	}
}
void* memory(int row, int col)
{
	int** mas;
	mas = (int**)calloc(row, sizeof(int*));
	for (int i = 0; i < col; i++)
	{
		*(mas + i) = (int*)calloc(col, sizeof(int));
	}
	return mas;
}
void free_matrix(int** mas, int row)
{
	for (int i = 0; i < row; i++)
		free(*(mas + i));
}
//void memory(int*** mas, int row, int col, int k)
//{
//	if (k == 0)
//	{
//		*mas = (int**)calloc(row, sizeof(int*));
//		for (int i = 0; i < row; i++)
//			(*mas)[i] = (int*)calloc(col, sizeof(int));
//	}
//	else
//	{
//		for (int i = 0; i < row; i++)
//			free((*mas)[i]);
//		free(*mas);
//	}
//}
void hand_input(int** mas, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		printf("Input row %d\n", i + 1);
		for (int j = 0; j < col; j++)
		{
			while (scanf_s("%d", *(mas + i)+j) != 1 || getchar() != '\n')
			{
				printf("Error\n");
				rewind(stdin);
			}
		}
	}
}
void random_input(int** mas, int row, int col)
{
	srand(time(NULL));
	for (int i = 0; i < row; i++)
	{
		for(int j=0; j<col; j++)
			*(* (mas + i) + j) = rand() % 21 - 10;
	}
}
void input_matrix(int** mas, int  row, int col, int choice)
{
	if (choice == 1)
		hand_input(mas, row, col);
	else
		random_input(mas, row, col);
}
void output_matrix(int** mas, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		printf("\n");
		for (int j = 0; j < col; j++)
			printf("%6d", *(*(mas + i) + j));
	}
}
int cnt_even_element(int** mas, int length, int r)
{
	int cnt = 0;
	for (int k = 0; k < length; k++)
	{
		if (*( * (mas + r) + k) % 2 == 0)
			cnt++;
	}
	return cnt;
}
void sort(int** mas, int row, int col)
{
	for (int i = 1; i < row; i++)
	{
		for (int j = i; j > 0 && cnt_even_element(mas, col, j - 1) < cnt_even_element(mas, col, j); j--)
		{
				for (int a = 0; a < col; a++)
				{
					int temp = mas[j][a];
					mas[j][a] = mas[j-1][a];
					mas[j-1][a] = temp;
				}
		}
	}
}