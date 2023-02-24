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
		printf("Make right choiсe(1-5):");
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

int delete(vacuum* array, int k, int* size)
{
	if (array != NULL)
	{
		for (int i = k; i < (*size) ; i++)
			array[i-1] = array[i];
		(*size)--;
		if (array != NULL)
		{
			vacuum *storer = (vacuum*)realloc(array, (*size) * sizeof(vacuum));
			save("filec.txt", storer, *size);
		}
	}
	//free(storer);
	return 0;
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
		}
	}
}

void sort_one_field(vacuum* array, int size)
{

	int choice1 = NULL;
	printf("What criteries\n1.Producer\n2.Status\n3.Price\n");
	
	scanf("%d", &choice1);

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size - 1; j++)
			if (variant_of_sort(choice1, j, array) == 1)
			{
				vacuum storer = array[j];
				array[j] = array[j + 1];
				array[j + 1] = storer;
			}
}

int variant_of_sort(int field, int counter, vacuum* mas)
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
	printf("|     Producer    |       Status       |    Price    | \n");
	printf("|----------------------------------------------------| \n");

	while (i < n)
	{
		char* temp= (char*)calloc(5, sizeof(char));
		if (p[i].status == OUT)
			strcpy(temp, "in");
		else
			if (p[i].status == IN)
				strcpy(temp, "out");
			else
				break;
		printf("| %-16s| %-19s| %-12.3f|\n", p[i].producer, temp, p[i].price);
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
	char ptr[5];
	const static char* stat[] = { "in","out" };
	int j=0;
	int i = 0;
	vacuum* temp = (vacuum*)realloc(p, ((n + 1) * sizeof(vacuum)));
			
	temp = temp + n;
	temp->producer = (char*)calloc(10, sizeof(char));
	printf("Input producer:\n");
	scanf("%s", temp->producer);
	printf("Input status:\n");
	scanf("%s", ptr);
	if (!strcmp(stat[0], ptr))
			j = 0;
	if (!strcmp(stat[1], ptr))
			j = 1;
	temp[0].status = j;
	printf("Input price:\n");
	scanf("%f", &temp->price);
	temp = temp - n;
	save("filec.txt", temp, (n + 1));
	printf("Zapis dobavlena:\n");
	for (int i = 0; i <= n; i++)
		free((temp + i)->producer);
	free(temp);
	return 0;
}

int add_menu()
{
	int size = count("filec.txt");
	vacuum* array = load("filec.txt");
	add(array, size);
	return 0;
}

int save(char* filename, vacuum* p, int n)
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
		char temp[4];

		if (p[i].status == IN)
			strcpy(temp, "in");
		if (p[i].status == OUT)
			strcpy(temp, "out");
		fprintf(fp, "%s %s %.3f\n", p[i].producer, temp, p[i].price);
		i++;
	}
	fclose(fp);
	return 0;
}

vacuum* load(char* filename)
{
	FILE* fp;
	int n, i = 0;
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
		return NULL; // если памяти не хватило.
	while (i < n) 
	{
		char* ptr = (char*)calloc(5, sizeof(char));
		fscanf(fp, "%s%s%f", temp[i].producer, ptr, &temp[i].price);
		if (strcmp(ptr, "in"))
			temp[i].status = IN;
		else
			if (strcmp(ptr, "out"))
				temp[i].status = OUT;
			else
				break;
		i++;
	}
	fclose(fp);
	return temp;
}

int count(char* filename)
{
	FILE* fp;
	int n;
	if ((fp = fopen(filename, "r")) == NULL)
	{
		perror("Error occured while opening file");
		exit(1);
	}
	fscanf(fp, "%d\n", &n);
	fclose(fp);
	return n;
}

void sort_one_field_menu()
{
	int size = count("filec.txt");
	vacuum* array = load("filec.txt");
	
	int choice1 = NULL;
	printf("What criteries\n1.Producer\n2.Status\n3.Price\n");

	scanf("%d", &choice1);
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