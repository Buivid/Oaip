#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void check_choice_task(int* ch)
{
    while (scanf_s("%d", ch) != 1 || *ch != 1 && *ch != 2 && *ch != 3 || getchar() != '\n')
    {
        printf("Ошибка.Попробуй снова\nВыберите задание:");
        rewind(stdin);
    }
}
void check_go_choice(int* ch)
{
    while (scanf_s("%d", ch) != 1 || *ch != 1 && *ch != 2 || getchar() != '\n')
    {
        printf("Ошибка.Попробуй снова\nОтвет:");
        rewind(stdin);
    }
}
char* memory()
{
    char* str = (char*)calloc(1024, sizeof(char));
    return str;
}
int count_word(char* str)
{
    int i, flag, cnt;
    for (i = 0, flag = 0, cnt = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.' || str[i] == '-' || str[i] == '\t')
            flag = 0;
        else
        {
            if (flag == 0)
            {
                cnt++;
                flag = 1;
            }
        }
    }
    return cnt;
}
void input_str(char** str)
{
    do
    {
        printf("Введите строку:");
        fgets(*str, 1024, stdin);
        rewind(stdin);
    } while (str_len(*str) < 1 && getchar() != '\0');
    char* mas = (char*)realloc(*str, (str_len(*str) + 2) * sizeof(char));
    if (mas != NULL)
        *str = mas;
    // (/n)
}
int str_len(char* str)
{
    int i = 0;
    while (str[i] != '\0')
        i++;
    return i + 1;
}
void check_symbol(char* a)
{
    printf("Введите символ,вхождение которого вы хотите удвоить в строке:");
    while (scanf_s("%c", a, 1) != 1 || getchar() != '\n')
    {
        printf("Ошибка.Попробуй снова\nВведите символ,вхождение которого вы хотите удвоить в строке:");
        rewind(stdin);
    }
}
void adding_symbol(char** str, char symbol)
{
    int size = str_len(*str);
    for (int i = 0; i < size; i++)
    {
        if (*(*str + i) == symbol)
        {
            char* mas = (char*)realloc(*str, (size + 3) * sizeof(char));
            if (mas != NULL)
                *str = mas;
            size++;
            for (int j = size - 1; j > i + 1; j--)
            {
                *(*str + j) = *(*str + j - 1);
            }
            *(*str + i + 1) = *(*str + i);
            i++;
        }
    }
}
void first_task(void)
{
    int word_count = 0;
    char* str = memory();
    input_str(&str);
    word_count = count_word(str);
    printf("Количество слов в строке: %d", word_count);
}
void second_task(void)
{
    char* str = memory();
    char symbol;
    input_str(&str);
    check_symbol(&symbol);
    adding_symbol(&str, symbol);
    printf("Итоговая строка:");
    fputs(str, stdout);
}