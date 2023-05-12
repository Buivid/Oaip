#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"func_decompress.h"

void func(const char* file_name)
{
    FILE* f;
    string* split_text = (string*)calloc(1, sizeof(string));
    split_text->len = 0;
    split_text->str = NULL;
    char* str = (char*)calloc(1024, sizeof(char));
    glossary* words = NULL;
    int size = 0;
    int file_size;
    int n;

    if ((f = fopen(file_name, "r")) == NULL)
        exit(1);

    fseek(f, 0, SEEK_END);
    file_size = ftell(f);
    printf("Original file - %d bytes\n", file_size);
    fseek(f, 0, SEEK_SET);
    fgets(str, 64, f);
    do
    {
        
        n = strlen(str);
     
        vocabulary(str, &words, &size);
        fgets(str, 64, f);

    } while (str[0] != '|');
    fgets(str, 1024, f);
    do
    {
        str_tok(str, " ", &split_text);
        fgets(str, 1024, f);
       
    } while (!feof(f));
    free(str);
    fclose(f);
    create_new_file(words, size, file_name, &split_text);
}

void str_tok(char* str1, const char* str2, string** text)
{
    int size1 = strlen(str1);
    string* token = (string*)calloc(1, sizeof(string));
    int pos1;
    string znak;
    if (str1 == NULL)
    {
        exit(1);
    }
    for (int i = 0; i < size1; i++)
    {
        if (str1[i] < 'A' || str1[i] > 'z')
        {
            znak.len = 1;
            znak.str = (char*)calloc(znak.len, sizeof(char));
            znak.str[0] = str1[i];
            add_to_text(text, znak.str);
        }
        if ((str1[i] < 'A' || str1[i] > 'z') && (str1[i + 1] >= 'A' && str1[i + 1] <= 'z'))
        {
            pos1 = i + 1;
            token->len = size_word(str1 + pos1);
            token->str = (char*)calloc(token->len + 1, sizeof(char));
            strncpy(token->str, str1 + pos1, token->len);

            add_to_text(text, token->str);
            i = pos1 + token->len - 1;
        }
        if (i == 0 && str1[i] >= 'A' && str1[i] <= 'z')
        {
            pos1 = i;
            token->len = size_word(str1 + pos1);
            token->str = (char*)calloc(token->len + 1, sizeof(char));
            strncpy(token->str, str1 + pos1, token->len);

            add_to_text(text, token->str);
            i = pos1 + token->len - 1;
        }
    }
    free(token);
}

void add_to_text(string** text, char* word)
{
    (*text)->str = (char**)realloc((*text)->str, ((*text)->len + 1) * sizeof(char*));
    (*text)->str[(*text)->len++] = word;
}

void vocabulary(char* str, glossary** words, int* size)
{
    *words = (glossary*)realloc(*words, (*size + 1) * sizeof(glossary));
    int i = 0;
    int n=0;
    int j;
    string* token = (string*)calloc(1, sizeof(string));

    n = size_word(str);
    token->len = n;
  
    token->str = (char*)calloc(n+1, sizeof(char));
    strncpy(token->str, str, token->len);
    (*words)[*size].big.word = *token;
    (*words)[*size].big.count = 0;
    i = size_word(str + n+1);
    
    token->len = i;
    token->str = (char*)calloc(i + 1, sizeof(char));
    strncpy(token->str, str+n+1, token->len);
    (*words)[*size].small.word = *token;
    (*words)[*size].small.count = 0;
    (*size)++;



 
    free(token);
}

void create_new_file(glossary* book, int size, const char* file_name, string** text)
{
    FILE* new_file;
    int file_size;
    if ((new_file = fopen("../2Lab2/New_file.txt", "w+")) == NULL)
        exit(1);
    fseek(new_file, 0, SEEK_SET);

    for (int i = 0; i < size; i++)
    {
        swap_words(text, (book + i));
    }
    for (int i = 0; i < (*text)->len; i++)
    {
        fputs((*text)->str[i], new_file);
    }
    file_size = ftell(new_file);
    printf("Decompression file - %d bytes", file_size);
    fclose(new_file);
}

void swap_words(string** text, glossary* word)
{
    for (int i = 0; i < (*text)->len; i++)
    {
        if (strcmp((*text)->str[i], word->big.word.str) == 0)
        {
            (*text)->str[i] = word->small.word.str;
        }
        else if (strcmp((*text)->str[i], word->small.word.str) == 0)
        {
            (*text)->str[i] = word->big.word.str;
        }
    }
}

int size_word(char* p)
{
    int count = 0;
    while (*p >= 'A' && *p <= 'z')
    {
        count++;
        p++;
    }
    return count;
}

//char* multi_tok(char* input, char* delimiter)
//{
//    static char* string;
//    if (input != NULL)
//        string = input;
//
//    if (string == NULL)
//        return string;
//
//    char* end = strstr(string, delimiter);
//    if (end == NULL) 
//    {
//        char* temp = string;
//        string = NULL;
//        return temp;
//    }
//
//    char* temp = string;
//
//    *end = '\0';
//    string = end + strlen(delimiter);
//    return temp;
//}
//
//string* split(char* input, char* delimiter) 
//{
//
//    string* str = malloc(sizeof(string));
//    str->str = NULL;
//    str->len = 0;
//
//    char* token = multi_tok(input, delimiter);
//
//    while (token != NULL) 
//    {
//        str->str = realloc(str->str, (str->len + 1) * sizeof(char*));
//        str->str[str->len++] = token;
//
//        token = multi_tok(NULL, delimiter);
//    }
//    return str;
//}
//
//char* file_read(char path[]) {
//
//    long length;
//    FILE* f = fopen(path, "rb");
//
//    if (f == NULL) return NULL;
//
//    fseek(f, 0, SEEK_END);
//    length = ftell(f);
//    fseek(f, 0, SEEK_SET);
//    char* buffer = calloc(length, 1);
//
//    fread(buffer, 1, length, f);
//    fclose(f);
//
//    return buffer;
//}