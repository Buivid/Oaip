#include<stdio.h>
#include<stdlib.h>
#include"arrays.h"
#include<locale.h>
main()
{
	setlocale(LC_ALL, "RUS");
	printf("В двумерном массиве целых чисел удалить все отрицательные элементы. Количество чисел в строке может быть различным, последнее число - 100\n");
	int** array;
	int row;

	printf("Введите количество строк\n");
	row = check_number_of_elements();
	memory(&array, row, 0);
	input_row(array, row);
	output_matrix(array, row);
	delete_neg_elements(array, row);
	printf("\nНовая матрица\n");
	output_matrix(array, row);
	memory(&array, row, 1);
	return 0;
}