#define _CRT_SECURE_NO_WARNINGS

#include"functions.h"

int main()
{
    system("color 0A");
  // setlocale(LC_ALL, 'RUS');
  
    node *head = NULL;
    //loadingBar();
    system("cls");
    func("Ulysses.txt", &head);
    //printf("%s %d %d", head->word, head->count, head->length);
    //show_stack(head);
    return 0;
}