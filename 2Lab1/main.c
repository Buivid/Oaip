#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"func.h"

#define EXIT 6

int main()
{
    void (**menu)() = (void(**)())calloc(5, sizeof(void(*)()));

    if (menu != NULL)
    {
        menu[0] = view_menu;
        menu[1] = delete_menu;
        menu[2] = sort_one_field_menu;
        //menu[3] = sort_two_field;
        menu[4] = add_menu;
        int choice = 0, task_choice = 0;

        do {
            printf("  Menu:\n1.Show catalog.\n2.Delete 1 pair.\n3.Sort one field.\n4.Sort two fields.\n5.Add element.\n6.Exit.\nYour choice:");
            menu_correct(&task_choice);
            system("cls");

            if (task_choice == EXIT)
            {
                free(menu);
                return 0;
            }
           
             menu[task_choice - 1]();

            printf("\nDo you want to continue?(Yes-1/No-0):");
            choice_continue(&choice);
            system("cls");
        } while (choice == 1);
    }

    free(menu);

    return 0;
}

