#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <locale.h>
void first_task(void);
void second_task(void);
int main()
{
	setlocale(LC_ALL, "Rus");
	int choice_task = 0, go_choice = 0;
	void (**menu)() = NULL;
	menu = (void(**)())calloc(2, sizeof(void(*)()));
	if (menu != NULL)
	{
		menu[0] = first_task;
		menu[1] = second_task;
		do
		{
			printf("Меню заданий:\n1.Дана строка. Найти количество слов в ней.\n2.Дан символ C и строка S. Удвоить каждое вхождение символа C в строку S.\n\nЕсли вы захотите закончить работу, то введите цифру <3>\n\nВыберите задание:");
			check_choice_task(&choice_task);
			if (choice_task == 3)
				return 0;
			system("cls");
			printf("%d задача.\n\n", choice_task);
			menu[choice_task - 1]();
			printf("\n\nХочешь вернуться в меню?\n1-Да\n2-Нет\n\nОтвет:");
			check_go_choice(&go_choice);
			system("cls");
		} while (go_choice == 1);
		return 0;
	}
}