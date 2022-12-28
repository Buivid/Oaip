#include<stdio.h>
#include<stdlib.h>
#include"functions.h"

#define SIZE (argc-1)

int main(int argc, char** argv)
{
	if (argc < 2)
		return 0;
	char** mas = (char**)malloc((argc) * sizeof(char*));
	if (mas == NULL)
		return 1;
	for (int i = 0; i < argc; i++)
		*(mas + i) = (char*)calloc(1, sizeof(char));
	for (int i = 1; i < argc; i++)
	{
		int j = 0;
		while (*(*(argv + i) + j) != '=')
		{
			if (*(mas + i - 1) == NULL)
				return 1;
			*(*(mas + i - 1) + j) = *(*(argv + i) + j);
			j++;
			if (j != 0)
			{
				char* storer;
				storer = (char*)realloc(*(mas + i - 1), (j + 1) * sizeof(char));
				if (*(mas + i - 1) != NULL)
					*(mas + i - 1) = storer;

			}
		}
		if (*(mas + i - 1) == NULL)
			return 1;
		*(*(mas + i - 1) + j + 1) = '\0';
	}
	printf("\nArray:\n");
	output_array(mas, SIZE);
	sort(mas, SIZE);
	printf("\nResult:\n");
	output_array(mas, SIZE);
	free(mas);
	return 0;
}