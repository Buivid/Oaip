#include <stdio.h>
#include<stdlib.h>
#include"arrays.h"
#include<locale.h>

int main()
{
	setlocale(LC_ALL, "RUS");
	printf("Заполнить массив с клавиатуры. Удалить все повторяющиеся числа (оставить только первое вхождение каждого числа)\n");
	int* array;
	int num_of_elem;
	printf("Введите количество элементов в массиве\n");
	num_of_elem = check_number_of_elements();
	memory(&array, num_of_elem, 0);
	printf("%p\n", array);
	printf("%p\n", &array);
	printf("Введите массив\n");
	hand_input_array(array, num_of_elem);
	output_array(array, num_of_elem);
	
	del_double(array, &num_of_elem);

	printf("\nНовый массив\n");
	output_array(array, num_of_elem);
	memory(&array, num_of_elem, 1);

	return 0;
}