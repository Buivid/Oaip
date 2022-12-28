#include <stdio.h>
#include<stdlib.h>
#include <time.h>
void memory(int*** mas, int row, int k)
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
void output_matrix(int** mas, int size, int* length)
{
	for (int i = 0; i < size; i++)
	{
		printf("\n");
		for (int j = 0; j < *(length + i); j++)
			printf("%6d ", *(*(mas + i) + j));

	}
}
void rand_input_matrix_3(int** mass, int size, int* length)
{

	srand(time(NULL));
	for (int i = 0; i < size; i++)
	{
		printf("Введите количество элементов в строке номер: %d\n", i + 1);
		scanf_s("%d", length + i);
		*(mass + i) = (int*)calloc(*(length + i), sizeof(int));
		for (int j = 0; j < *(length + i); j++)
			*(*(mass + i) + j) = rand() % 21 - 10;
	}
}
void shift_strings(int** mas, int size, int* length, int k)
{
	for (int i = 0; i < size; i++)
	{
		int cnt = k;
		while (cnt > 0)
		{
			int temp = *(*(mas + i));
			for (int j = 0; j < *(length + i) - 1; j++)
				*(*(mas + i) + j) = *(*(mas + i) + j + 1);
			*(*(mas + i) + (*(length + i) - 1)) = temp;
			cnt--;
		}
	}
}
int check_choice()
{
	int choice;
	while (scanf_s("%d", &choice) != 1 || choice != 1 && choice != 2 && choice != 3 || getchar() != '\n')
	{
		printf("Неверный ввод\n");
		rewind(stdin);
	}
	return choice;
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
void check_input(int* temp)
{
	while (scanf_s("%d", temp) != 1 || getchar() != '\n' || *temp < 1 || *temp > 2)
	{
		printf("Неверный ввод\n");
		rewind(stdin);
	}
	return temp;
}
void hand_input_matrix3(int** mas, int size, int* length)
{
	for (int i = 0; i < size; i++)
	{
		printf("Введите количество элементов в строке номер: %d\n", i + 1);
		scanf_s("%d", (length + i));
		printf("Введите элементы\n");
		*(mas + i) = (int*)calloc(*(length + i), sizeof(int));
		for (int j = 0; j < *(length + i); j++)
		{
			while (scanf_s("%d", *(mas + i) + j) != 1 || getchar() != '\n')
			{
				printf("Неверный ввод\n");
				rewind(stdin);
			}
		}
	}
}
void input_matrix3(int** mas, int* length, int size, int choice)
{
	switch (choice)
	{
	case 1:
		hand_input_matrix3(mas, size, length);
		break;
	case 2:
		rand_input_matrix_3(mas, size, length);
		break;
	}
}
