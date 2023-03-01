#define _CRT_SECURE_NO_WARNINGS
#define OUT_OF_MEMORY_EXCEPTION 4
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<locale.h>
#include"func.h"

#define EQUAL 2
#define NEED_CHANGE 1
#define NO_CHANGE 0 

#define FIRST_FIELD 1
#define SECOND_FIELD 2
#define THIRD_FIELD 3

vacuum* create()
{   
	vacuum* temp = NULL;
	if (!(temp = (vacuum*)malloc(sizeof(vacuum))))
		exit(OUT_OF_MEMORY_EXCEPTION);
	if(!(temp->producer = (char*)malloc(10)))
		exit(OUT_OF_MEMORY_EXCEPTION);
	return temp;
}

void menu_correct(int* task)
{
	while ((scanf_s("%d", task)) != 1 || *task < 1 || *task>6 || getchar() != '\n')
	{
		printf("Make right choiñe(1-5):");
		rewind(stdin);
	}
}

void choice_continue(int* num)
{
	while ((scanf_s("%d", num)) != 1 || getchar() != '\n' || *num < 0 || *num > 1)
	{
		printf("Intput correct number:");
		rewind(stdin);
	}
}

void correct_choice_delete(int* num, int size)
{
	while ((scanf_s("%d", num)) != 1 || *num < 1 || *num>size || getchar() != '\n')
	{
		printf("Incorrect choice(1-%d):", size);
		rewind(stdin);
	}
}

void delete_menu()
{
	int size = count("filec.txt");
	vacuum* array = load("filec.txt");
	int num = 0;
	view(array, size);
	printf("What pair you want delete?\nYour choice(1-%d):", size);
	correct_choice_delete(&num, size);

	if (array != NULL)
	{
		delete_element(&array, num, &size);
	}

	system("cls");
	free(array);
	
}

void delete_element(vacuum** mas, int number, int* size)
{
	if (mas != NULL)
	{
		if (number < 60 && number>0)
		{
			for (int i = number; i < *size; i++)
			{
				mas[0][i - 1] = mas[0][i];
			}
		}

		(*size)--;


		vacuum* storer = (vacuum*)realloc(*mas, (*size) * sizeof(vacuum));
		if (storer != NULL)
		{
			*mas = storer;
			save("filec.txt", storer, *size);
		}
	}
}

void sort_one_field(vacuum* array, int size, int choice)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size - 1; j++)
			if (variant_of_sort(choice, j, array) == 1)
			{
				vacuum storer = array[j];
				array[j] = array[j + 1];
				array[j + 1] = storer;
			}
}

int variant_of_sort(int field, int counter, vacuum const *  mas)
{
	if (field == FIRST_FIELD)
	{
			return change_need((mas + counter)->producer, (mas + counter + 1)->producer);
	}

	if (field == SECOND_FIELD)
	{
		if (mas[counter].status > mas[counter + 1].status)
		{
			return NEED_CHANGE;
		}
		if (mas[counter].status == mas[counter + 1].status)
		{
			return EQUAL;
		}
	}

	if (field == THIRD_FIELD)
	{
		if (mas[counter].price > mas[counter + 1].price)
		{
			return NEED_CHANGE;
		}
		if (mas[counter].price == mas[counter + 1].price)
		{
			return EQUAL;
		}

	}

	return NO_CHANGE;
}

void view(vacuum* p, int n)
{

	int i = 0;
	printf(".----------------------------------------------------. \n");
	printf("|     Producer    |        Wire        |    Price    | \n");
	printf("|----------------------------------------------------| \n");

	while (i < n)
	{
		int j=NULL;
		static char* status_name[] = {"wired", "wireless"};
		if (p[i].status == WIRED)
			j = 0;
		else
			if (p[i].status == WIRELESS)
				j = 1;
		printf("| %-16s| %-19s| %-12.2f|\n", p[i].producer, status_name[j], p[i].price);
		printf("|----------------------------------------------------| \n");
		i++;
	}
}

void view_menu()
{
	int size = count("filec.txt");
	vacuum* array = load("filec.txt");
	view(array, size);
	free(array);
}

int add(vacuum* p, int n)
{
	char ptr[10];
	int i = 0;
	vacuum* temp = (vacuum*)realloc(p, ((n + 1) * sizeof(vacuum)));

	temp = temp + n;
	temp->producer = (char*)calloc(10, sizeof(char));
	printf("Input producer:\n");
	scanf("%9s", temp->producer);

	printf("Input wire/wireless:\n");
	scanf("%4s", ptr);
	
	if (strcmp(ptr, "wired") == 0)
		temp[i].status = WIRED;
	else
		if (strcmp(ptr, "wireless")==0)
			temp[i].status = WIRELESS;
	printf("Input price:\n");
	scanf("%f", &temp->price);
	temp = temp - n;
	save("filec.txt", temp, (n + 1));
	printf("Vacuum cleaner was added:\n");
	for (int i = 0; i <= n; i++)
		free((temp + i)->producer);
	free(temp);
	return 0;
}

void add_menu()
{
	int size = count("filec.txt");
	vacuum* array = load("filec.txt");
	add(array, size);
}

int save(char const * filename, vacuum* p, int n)
{
	FILE* fp;
	if ((fp = fopen(filename, "w")) == NULL)
	{
		perror("Error occured while opening file");
		return 1;
	}
	fprintf(fp, "%d\n", n);
	int i = 0;
	while (i < n) 
	{
		char temp[10];

		if (p[i].status == WIRED)
			strcpy(temp, "wired");
		if (p[i].status == WIRELESS)
			strcpy(temp, "wireless");
		fprintf(fp, "%s %s %.3f\n", p[i].producer, temp, p[i].price);
		i++;
	}
	fclose(fp);
	return 0;
}

vacuum* load(char const* filename)
{
	FILE* fp;
	int n; int i = 0;
	if ((fp = fopen(filename, "r")) == NULL)
	{
		perror("Error occured while opening file");
		exit(1);
	}
	fscanf(fp, "%d\n", &n);
	
	vacuum* temp = (vacuum*)malloc(n * sizeof(vacuum));
	for(int j=0; j<n; j++)
		(temp + j)->producer = (char*)malloc(10 * sizeof(char));

	if (!temp)
		return NULL; 
	while (i < n) 
	{
		char* ptr = (char*)calloc(10, sizeof(char));
		if (!ptr)
			return NULL;

		fscanf(fp, "%s%s%f", temp[i].producer, ptr, &temp[i].price);
		if (strcmp(ptr, "wired")==0)
			temp[i].status = WIRED;

		else
				temp[i].status = WIRELESS;
		i++;
		free(ptr);
	}
	fclose(fp);
	return temp;
}

int count(char const *  filename)
{
	FILE* fp;
	int n;
	if ((fp = fopen(filename, "r")) == NULL)
	{
		perror("Error occured while opening file");
		exit(1);
	}
	while(fscanf(fp, "%d\n", &n)!=1)
		printf("Error\n");
	fclose(fp);
	return n;
}

void sort_one_field_menu()
{
	int size = count("filec.txt");
	vacuum* array = load("filec.txt");
	
	int choice1 = NULL;
	printf("What criteries\n1.Producer\n2.Status\n3.Price\n");

	while (scanf("%d", &choice1) != 1 || (choice1 < 1 && choice1>3))
	{
		printf("Incorrect input\n");
		rewind(stdin);
	}

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size - 1; j++)
			if (variant_of_sort(choice1, j, array) == 1)
			{
				vacuum storer = array[j];
				array[j] = array[j + 1];
				array[j + 1] = storer;
			}

	view(array, size);
	for (int i = 0; i < size; i++)
		free((array + i)->producer);
	free(array);
}

int change_need(const char* str1, const char* str2)
{
	size_t size;
	if (strlen(str1) > strlen(str2))
		size = strlen(str2);
	else
		size = strlen(str1);
	for (int i = 0; i < size + 1; i++)
	{
		if (*(str1 + i) > *(str2 + i))
			return NEED_CHANGE;
		if (*(str1 + i) < *(str2 + i))
			return NO_CHANGE;
	}
	return EQUAL;
}

void sort_by_two_fields_menu()
{
	int size = count("filec.txt");
	vacuum* array = load("filec.txt");
	int choice1 = NULL; 
	int choice2 = NULL;

	printf("What first criteries\n1.Producer\n2.Status\n3.Price\n");
	while (scanf("%d", &choice1) != 1 || (choice1 != 1 && choice1 != 2 && choice1 != 3 )|| getchar() != '\n')
	{
		printf("Error!!!");
		rewind(stdin);
	}

	printf("What second criteries\n1.Producer\n2.Status\n3.Price\n");
	while (scanf("%d", &choice2) != 1 || (choice2 != 1 && choice2 != 2 && choice2 != 3) || getchar() != '\n')
	{
		printf("Error!!!");
		rewind(stdin);
	}

	switch (choice1)
	{
	case 1:
		if (choice2 == 2)
			by_producer_status(array, size);
		if (choice2 == 3)
			by_producer_price(array, size);
		if (choice2 == 1)
		{
			printf("You chose same fields\n");
			rewind(stdin);
		}
		break;
	case 2:
		if (choice2 == 1)
			by_status_producer(array, size);
		if (choice2 == 3)
			by_status_price(array, size);
		if (choice2 == 2)
		{
			printf("You chose same fields\n");
			rewind(stdin);
		}
		break;
	case 3:
		if (choice2 == 1)
			by_price_producer(array, size);
		if (choice2 == 2)
			by_price_status(array, size);
		if (choice2 == 3)
		{
			printf("You chose same fields\n");
			rewind(stdin);
		}
		break;
	default:
		printf("Catalog is not sorted");
		break;
	}
	view(array, size);
}

void by_producer_status(vacuum *array, int size)
{
	sort_one_field(array, size, 1);
	for (int i = 0; i < size; i++)
		for (int j = size-1; j >i; j--)
		{
			if (strcmp((array + i)->producer, (array + j)->producer) ==0 && array[j-1].status > array[j].status)
			{
				vacuum storer = array[j - 1];
				array[j - 1] = array[j];
				array[j] = storer;
			}
		}
}

void by_producer_price(vacuum* array, int size)
{
	sort_one_field(array, size, 1);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size - 1; j++)
		{
			if (strcmp((array + j)->producer, (array + j + 1)->producer)==0)
			{
				if (variant_of_sort(3, j, array) == 1)
				{
					vacuum storer = array[j];
					array[j] = array[j + 1];
					array[j + 1] = storer;
				}
			}
		}
}

void by_status_producer(vacuum* array, int size)
{
	sort_one_field(array, size, 2);
	for (int i = 0; i < size; i++) 
	{
		for (int j = size-1; j>i; j--)
		{
			if (array[i].status == array[j].status && strcmp((array + j - 1)->producer, (array + j)->producer) > 0)
			{

				vacuum storer = array[j - 1];
				array[j - 1] = array[j];
				array[j] = storer;
			}
		}
	}
}

void by_status_price(vacuum* array, int size)
{
	sort_one_field(array, size, 2);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size - 1; j++)
		{
			if (array[j].status == array[j + 1].status)
			{
				if (variant_of_sort(3, j, array) == 1)
				{
					vacuum storer = array[j];
					array[j] = array[j + 1];
					array[j + 1] = storer;
				}
			}
			
		}
}

 void by_price_producer(vacuum *array, int size)
 {
	sort_one_field(array, size, 3);
	for (int i = 0; i < size; i++)
		for (int j = size-1; j >i; j--)
		{
			if (array[j].price == array[j + 1].price)
			{
				if (variant_of_sort(1, j, array) == 1)
				{
					vacuum storer = array[j];
					array[j] = array[j + 1];
					array[j + 1] = storer;
				}
			}
		}
 }

void by_price_status(vacuum* array, int size)
{
	sort_one_field(array, size, 3);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size - 1; j++)
		{
			if (array[j].price == array[j + 1].price)
			{
				if (variant_of_sort(2, j, array) == 1)
				{
					vacuum storer = array[j];
					array[j] = array[j + 1];
					array[j + 1] = storer;
				}
			}
			else
				break;
		}
}

