#include <stdio.h>
#include<stdlib.h>
#include <time.h>
void memory(int ***mas, int row, int k)
{
	if (k == 0)
	{
		*mas = (int**)calloc(row, sizeof(int*));
		for (int i = 0; i < row; i++)
			(*mas)[i] = (int*)calloc(1, sizeof(int));
	}
	else
	{
		for (int i = 0; i < row; i++)
			free((*mas)[i]);
		free(*mas);
	}
}
void input_row(int** mas, int row)
{
	int m = 1;
	for (int i = 0; i < row; i++)
	{
		printf("Введите строку %d\n", i + 1);
		for (int j = 0; j < m; j++)
		{
			scanf_s("%d", &mas[i][j]);
			if (mas[i][j] == 100)
				break;
			else
			{
				m++;
				mas[i] = (int*)realloc(mas[i], m * sizeof(int));
			}
		}
		m = 1;
	}
}
void output_matrix(int** mas, int row)
{
	int m=1;
	for (int i = 0; i < row; i++)
	{
		for(int j=0; j<m; j++)
			if (mas[i][j] == 100)
			{
				printf("%6d", mas[i][j]);
				printf("\n");
				break;
			}
			else
			{
				printf("%6d ", *(*(mas + i) + j));
				m++;
			}
	}
}
void delete_neg_elements(int** mas, int size)
{
	int cnt;
	for (int i = 0; i < size; i++)
	{
		int j = 0;
		while (mas[i][j] != 100)
		{
				if (*(*(mas + i) + j) < 0)
				{
					int k = j;
					while (mas[i][k] != 100)
					{
						*(*(mas + i) + k) = *(*(mas + i) + k + 1);
						k++;
						cnt = k + 1;
					}
					*(mas + i) = (int*)realloc(*(mas + i), sizeof(int) * (cnt));
					j--;
				}
				j++;
		}
	}
}
int check_number_of_elements()
{
	int arrsize;
	if (scanf_s("%d", &arrsize) != 1 || arrsize < 1 || getchar() != '\n')
	{
		printf("Неверный ввод\n");
		rewind(stdin);
		return check_number_of_elements();
	}
	else
		return arrsize;
}