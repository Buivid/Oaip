#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

main()
{
	int* array1, *array2, size, choice;
	printf("How would you like to enter the array?\n");
	printf("1. Hand input\n");
	printf("2. Random input\n");
	check_input(&choice);
	check_size(&size);
	array1 = memory(size);
	input_array(array1, size, choice);
	output_array(array1, size);
	array2 = memory(size);
	double_array(array1, array2, size);

	int left = 0, right = size - 1;
	clock_t start1 = clock();
	quick_sort(array1, left, right);
	clock_t end1 = clock();
	float time1 = (float)(end1 - start1) / CLOCKS_PER_SEC;
	printf("\nResult of Hoar sorting\n");
	output_array(array1, size);
	clock_t start2 = clock();
	bubble_sort(array2, size);
	clock_t end2 = clock();
	float time2 = (float)(end2 - start2) / CLOCKS_PER_SEC;
	printf("\nResult of Bubble sorting\n");
	output_array(array2, size);
	printf("\nHoar sort takes about %.6f seconds\n", time1);
	printf("\nBubble Sort takes about %.6f seconds\n", time2);
	time_compare(time1, time2);
	free(*array1);
	free(*array2);




	
	return 0;
}