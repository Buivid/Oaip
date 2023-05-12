#pragma once
#include<stdio.h>
#include<stdlib.h>

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

void func(const char* file_name);
void str_tok(char* str1, const char* str2, string** text);
void add_to_text(string** text, char* word);
void vocabulary(char* str, glossary** words, int* size);
void create_new_file(glossary* book, int size, const char* file_name, string** text);
void swap_words(string** text, glossary* word);
int size_word(char* p);
string* split(char* input, char* delimiter);
char* multi_tok(char* input, char* delimiter);
