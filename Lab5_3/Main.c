#include<stdio.h>
#include<stdlib.h>
#include"functions.h"
#include<locale.h>

int main()
{
	setlocale(LC_ALL, "RUS");
	printf("В двумерном массиве выполнить циклический сдвиг элементов каждой строки влево на k позиций (последние элементы перемещаются в начало)\n");
	int** matrix;
	int row, k;
	int* length;
	int choice3;
	printf("Способ ввода\n");
	printf("1. Ручной ввод\n");
	printf("2. Рандомный ввод\n");
	check_input(&choice3);
	printf("Введите количество строк\n");
	row = check_number_of_elements();
	memory(&matrix, row, 0);
	length = (int*)calloc(row, sizeof(int));
	input_matrix3(matrix, length, row, choice3);
	output_matrix(matrix, row, length);
	printf("\n\nВведите k = ");
	k = check_number_of_elements();
	shift_strings(matrix, row, length, k);
	output_matrix(matrix, row, length);
	memory(&matrix, row, 1);
}