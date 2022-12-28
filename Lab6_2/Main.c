#include<stdio.h>
#include<stdlib.h>
#include"functions.h"

void main()
{
	int** matrix, row, col, choice;

	printf("How do you want to input the matrix\n");
	printf("1.Hand input\n");
	printf("2.Random input\n");

	check_input(&choice);
	printf("Input number of the rows\n");
	check_size(&row);
	printf("Input number of the columns\n");
	check_size(&col);
	matrix = memory(row, col);
	//memory(&matrix, row, col, 0);
	input_matrix(matrix, row, col, choice);
	output_matrix(matrix, row, col);
	sort(matrix, row, col);
	printf("\nResult of sorting\n");
	output_matrix(matrix, row, col);
	//memory(&matrix, row, col, 1);
	//free(*matrix);
	free_matrix(*matrix, row);








	return 0;
}