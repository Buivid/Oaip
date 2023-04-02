#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

typedef struct node
{
    char* word;
    int count;
    int length;
    int mark;
    struct node* next;
}node;

typedef struct string
{
    char** str;
    int len;
}string;

typedef struct WORD
{
    string word;
    int count;
}WORD;

typedef struct glossary
{
    WORD big;
    WORD small;
}glossary;

node* check_word(node** head, char* str);
void add_word(string *str, node** head);
void func(char* file_name, node** head);
void push(node** head, string *str);
void str_tok(char* str1, char* str2, node** head, string** text);
void show_stack(node* head);
void replace_words(node** head, const char* file_name, string** text);
WORD pop(node** head);
int profit(node* head, WORD word);
void add_to_text(string** text, char* word);
void swap_words(string** text, glossary* word);
void create_new_file(glossary* book, int size, const char* file_name, string** text);
int size_word(char* p);
void loading_bar();