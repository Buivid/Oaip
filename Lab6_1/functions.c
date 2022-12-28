#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void* memory(int n)
{
	int* mas;
	mas = (int*)calloc(n, sizeof(int));
	return mas;
}
void hand_input(int* mas, int n)
{
	printf("Input array\n");
	for (int i = 0; i < n; i++)
	{
		while (scanf_s("%d", mas + i) != 1 || getchar() != '\n')
		{
			printf("Error\n");
			rewind(stdin);
		}
	}
}
void random_input(int* mas, int n)
{
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		*(mas + i) = rand() % 21 - 10;
}
void check_input(int* choice)
{
	while (scanf_s("%d", choice) != 1 || ( * choice != 1 && *choice != 2 )|| getchar() != '\n')
	{
		printf("Error\n");
		rewind(stdin);
	}
}
void check_size(int* size)
{
	printf("Input size of the array\n");
	while (scanf_s("%d", size) != 1 || *size < 1||getchar()!='\n')
	{
		printf("Error\n");
		rewind(stdin);
	}
}
void input_array(int* mas, int size, int choice)
{
	if (choice == 1)
		hand_input(mas, size);
	else
		random_input(mas, size);
}
void output_array(int* mas, int n)
{
	for (int i = 0; i < n; i++)
		printf("%6d ", *(mas + i));
}
void double_array(int* mas1, int* mas2, int n)
{
	for (int i = 0; i < n; i++)
		*(mas2 + i) = *(mas1 + i);
}
void quick_sort(int* mas, int left, int right)
{
	int pivot; 

	while (check_element(mas, right) == 1)
		right--;
	while (check_element(mas, left) == 1)
		left++;

	int l_hold = left; 
	int r_hold = right; 
	pivot = *(mas+left);

	while (left < right) 
	{
		while ((*(mas + right) >= pivot) && (left < right)) 
		{
			right--;
			while (check_element(mas, right) != 0)
				right--;
		}
		if (left != right) 
		{
			*(mas+left) = *(mas+right); 
			left++; 
			while (check_element(mas, left) != 0)
				left++;
		}
		while ((*(mas + left) <= pivot) && (left < right)) 
		{
			left++;
			while (check_element(mas, left) != 0)
				left++;
		} 

		if (left != right) 
		{
			*(mas+right) = *(mas+left); 
			right--; 
			while (check_element(mas, right) != 0)
				right--;
		}
	}
	*(mas+left) = pivot; 
	pivot = left;
	left = l_hold;
	right = r_hold;
	if (left < pivot) 
		quick_sort(mas, left, pivot - 1);
	if (right > pivot)
		quick_sort(mas, pivot + 1, right);
}
int check_element(int* mas, int step)
{
	if ((*(mas + step)) % 2 == 0)
		return 0;
	else
		return 1;
}
void bubble_sort(int* mas, int n)
{
	int temp;
	for (int i = 0; i < n-1; i++)
	{
		while (check_element(mas, i) == 1)
			i++;
		for (int j = i + 1; j < n; j++)
		{
			while (check_element(mas, j) == 1)
				j++;
			if (*(mas + i) > *(mas + j))
			{
				temp = *(mas + i);
				*(mas + i) = *(mas + j);
				*(mas + j) = temp;
				j--;
			}
		}
	}

}
void time_compare(float time1, float time2)
{
	if (time1 - time2 > 0)
		printf("\nBubble sort faster for %.6f seconds.\n", time1 - time2);
	if (time1 - time2 < 0)
		printf("\nHoar sort faster for %.6f seconds.\n", time2 - time1);
	if (time1 == time2)
		printf("\nThey are equal.\n");
}