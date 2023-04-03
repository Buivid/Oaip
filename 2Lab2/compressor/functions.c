#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"functions.h"


void push(node** head, string* data)
{
    node* tmp = (node*)malloc(sizeof(node));
    tmp->word = data->str;
    tmp->count = 1;
    tmp->length = data->len;
    tmp->mark = 0;
    tmp->next = (*head);
    (*head) = tmp;
}

void show_stack(node* head)
{
    while (head!=0)
    {
        printf("%s %d\n", head->word, head->count);
        head = head->next;
    }
}

node *check_word(node** head, string* str)
{
    node* temp = *head;
    while (temp != NULL)
    {
        if (strcmp(str->str, temp->word) != 0)
        {
            temp = temp->next;
        }
        else
        {
            temp->count +=1;
            break;
        }
    }
    if (temp == NULL)
    {
        push(head, str);
    }
    return head;
}

void add_word(string* str, node** head)
{
    if (*head == NULL)
        push(head, str);
    else
        head = check_word(head, str);
}

void func(const char* file_name, node** head)
{
    FILE* f;
    string* split_text = (string*)calloc(1, sizeof(string));
    split_text->len = 0;
    split_text->str = NULL;
    char* str = (char*)calloc(2000, sizeof(char));

    if ((f = fopen(file_name, "r")) == NULL)
        exit(1);
    
    fseek(f, 0, SEEK_END);
    printf("Original file - %ld bytes\n", ftell(f));
    fseek(f, 0, SEEK_SET);
    fgets(str, 2000, f);
    do
    {
        str_tok(str, " ", head, &split_text);
        fgets(str, 2000, f);
    } while (!feof(f));
    free(str);
    fclose(f);
    replace_words(head, file_name, &split_text);
}

void str_tok(char* str1, const char* str2, node** head, string** text)
{
    int size1 = strlen(str1);
    string* token = (string*)calloc(1, sizeof(string));
    int pos1;
    string znak;
    if (str1 == NULL)
    {
        exit(1);
    }
   for(int i = 0; i<size1; i++)
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
           token->str = (char*)calloc(token->len+1, sizeof(char));
           strncpy(token->str, str1 + pos1, token->len);
           add_word(token, head);
           add_to_text(text, token->str);
           i=pos1+ token->len-1;
       }
       if (i == 0 && str1[i] >= 'A' && str1[i] <= 'z')
       {
           pos1 = i;
           token->len = size_word(str1 + pos1);
           token->str = (char*)calloc(token->len+1, sizeof(char));
           strncpy(token->str, str1 + pos1, token->len);
           add_word(token, head);
           add_to_text(text, token->str);
           i = pos1 + token->len - 1;
       }    
   }
   free(token);
}

int size_word(char* p)
{
    int count=0;
    while (*p >= 'A' && *p <= 'z')
    {
        count++;
        p++;
    }
    return count;
}

void replace_words(node** head, const char *file_name, string** text)
{
    WORD small_word;
    WORD big_word;
    int size = 0;
    glossary* book = (glossary*)calloc(1, sizeof(glossary));
   
    while (*head) 
    {
        int cnt = 0;
        if ((*head)->mark == 0)
        {
            big_word = pop(head);
            node* temp = *head;
            node* mark_word_adress = NULL;
            int max_profit = 0;

            while (temp)
            {
                cnt++;
                if (profit(temp, big_word) != -1 && max_profit < profit(temp, big_word) && temp->mark == 0)
                {
                    max_profit = profit(temp, big_word);
                    small_word.word.len = temp->length;
                    small_word.word.str = (char*)calloc(small_word.word.len, sizeof(char));
                    small_word.word.str = temp->word;
                    small_word.count = temp->count;
                    mark_word_adress = temp;
                }
                temp = temp->next;
            }
            if (mark_word_adress == NULL)
                continue;
            else
            {
                temp = mark_word_adress;

                temp->mark = 1;
                book = (glossary*)realloc(book, ((size + 1) * sizeof(glossary)));
                book[size].big = big_word;
                book[size].small = small_word;
                size++;
            }
        }
        else
            pop(head);
    }
    create_new_file(book, size, text);
}

WORD pop(node** head)
{
    node* prev = NULL;
    WORD word;
    if (*head == NULL) {
        exit(-1);
    }
    prev = (*head);
    word.word.len = prev->length;
    word.word.str = (char*)calloc(word.word.len, sizeof(char));
    word.word.str = prev->word;
    word.count = prev->count;
    (*head) = (*head)->next;
    free(prev);
    return word;
}

int profit(node* head, WORD word)
{
    int profit;
    WORD big, small;
    big = word;
    small.word.len = head->length;
    small.word.str = (char*)calloc(small.word.len, sizeof(char));
    small.word.str = head->word;
    small.count = head->count;
    profit = (big.count * big.word.len + small.count * small.word.len) - (big.count * small.word.len + small.count * big.word.len + big.word.len + small.word.len + 2);
    if (profit <= 4)
        return -1;
    else
        return profit;  
}

void create_new_file(glossary* book, int size, string** text)
{
  
    FILE* file_compressed;
    int file_size;
   
    if ((file_compressed = fopen("Compressed.txt", "w+")) == NULL)
        exit(1);
    fseek(file_compressed, 0, SEEK_SET);
   
    for (int i = 0; i < size; i++)
    {
        fputs(book[i].big.word.str, file_compressed);
        fputs("-", file_compressed);
        fputs(book[i].small.word.str, file_compressed);
        fputs("\n", file_compressed);
    }
    fputs("|\n", file_compressed);
    for (int i = 0; i < size; i++)
    {
        swap_words(text, (book+i));
    }
    for (int i = 0; i < (*text)->len; i++)
    {
        fputs((*text)->str[i], file_compressed);
    }
    file_size = ftell(file_compressed);
    printf("Compression file - %d bytes", file_size);
    free(*text);
    fclose(file_compressed);
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

void add_to_text(string** text, char* word)
{
    (*text)->str = realloc((*text)->str, ((*text)->len + 1) * sizeof(char*));
    (*text)->str[(*text)->len++] = word;
}

void loading_bar()
{
    // 0 - black background,
    // A - Green Foreground
    system("color 0A");

    // Initialize char for printing
    // loading bar
    char a = 177, b = 219;

    printf("\n\n\n\n");
    printf("\n\n\n\n\t\t\t\t\t");
    printf( "Loading...\n\n");
    printf("\t\t\t\t\t");

    // Print initial loading bar
    for (int i = 0; i < 26; i++)
        printf("%c", a);

    // Set the cursor again starting
    // point of loading bar
    printf("\r");
    printf("\t\t\t\t\t");

    // Print loading bar progress
    for (int i = 0; i < 26; i++) {
        printf("%c", b);

        // Sleep for 1 second
        Sleep(1000);
    }
}