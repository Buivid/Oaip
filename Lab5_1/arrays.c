#include <stdio.h>
#include<stdlib.h>
#include <time.h>

void memory(int** mas, int size, int k)
{
	if (k == 0)
		*mas = (int*)calloc(size, sizeof(int));
	else
		free(*mas);
}
void hand_input_array(int* mass, int size)
{
	for (int i = 0; i < size; i++)
	{
		while (scanf_s("%d", (mass + i)) != 1 || getchar() != '\n')
		{
			printf("Неверный ввод\n");
			rewind(stdin);
		}
	}
}
void output_array(int* mass, int size)
{
	for (int i = 0; i < size; i++)
		printf("%d ", *(mass + i));
}
void del_double(int* mas, int* size)
{
	for (int i = 0; i < *size - 1; i++)
	{
		for (int j=i+1; j<*size; j++)
			if (*(mas + j) == *(mas + i))
			{
				for (int k = j; k < *size - 1; k++)
					*(mas + k) = *(mas + k + 1);
				(* size)--;
				j--;
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