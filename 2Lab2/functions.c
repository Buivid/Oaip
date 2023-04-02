#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"functions.h"
#include<locale.h>


void push(node** head, string* data)
{
    //show_stack(*head);
    //printf("%s", data->str);
    node* tmp = (node*)malloc(sizeof(node));
   /* node* h2 = (node*)malloc(sizeof(node));
    h2 = *head;*/
   // tmp->word = (char*)calloc(data->len, sizeof(char));
    tmp->word = data->str;
    tmp->count = 1;
    tmp->length = data->len;
    tmp->mark = 0;
    tmp->next = (*head);
    (*head) = tmp;
   // printf("!\n");
   // show_stack(*head);
   // printf("push %x\n", *head);
   // printf("%s ", (*head)->word);
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
    //printf("check word %x\n", *head);
    node* temp = *head;
    while (temp != NULL)
    {
        if (strcmp(str->str, temp->word) != 0)
        {
            temp = temp->next;
        }
        else
        {
            //printf("aha\n");
            temp->count +=1;
            break;
        }
    }
    if (temp == NULL)
    {
        push(head, str);
       // printf("+\n");
    }
   // show_stack(*head);
    return head;
}

void add_word(string* str, node** head)
{
    if (*head == NULL)
        push(head, str);
    else
        head = check_word(head, str);
   // printf("add word %x\n", *head);
   // show_stack(*head);
}

void func(char* file_name, node** head)
{
    FILE* f;
    string* split_text = (string*)calloc(1, sizeof(string));
    split_text->len = 0;
    split_text->str = NULL;
    char* str = (char*)calloc(1024, sizeof(char));
    int c = 0;

    if ((f = fopen(file_name, "r")) == NULL)
        exit(1);
    
    fseek(f, 0, SEEK_END);
    printf("Original file - %d bytes\n", ftell(f));
    fseek(f, 0, SEEK_SET);

    while (!feof(f))
    {
        fgets(str, 1024, f);
        str_tok(str, " ", head, &split_text);
        c++;
        //printf("%d\n", c);
    }
    fclose(f);
    replace_words(head, file_name, &split_text);
}

void str_tok(char* str1, const char* str2, node** head, string** text)
{
    int size1 = strlen(str1);
    int size2 = strlen(str2);
    string* token = (string*)calloc(1, sizeof(string));
    int pos1;
    int pos2 = size1 - 1;
    string znak;
    /*if (str1 == NULL)
    {
        exit(1);
    }*/
    //printf("%s\n", str1);
   for (int i = 0; i<size1-1; i++)
   {
           if (str1[i] < 'A' || str1[i] > 'z')
           {
               //printf("%c", str1[i]);
               znak.len = 1;
               znak.str = (char*)calloc(token->len, sizeof(char));
               znak.str[0] = str1[i];
              // printf("%c\n", znak.str[0]);
               add_to_text(text, znak.str);
           }
           if ((str1[i] < 'A' || str1[i] > 'z') && (str1[i + 1] >= 'A' && str1[i + 1] <= 'z'))
           {
               pos1 = i + 1;
               token->len = size_word(str1 + pos1);
               token->str = (char*)calloc(token->len+1, sizeof(char));
               strncpy(token->str, str1 + pos1, token->len);
               add_word(token, head);
               //printf("%s", token->str);
               add_to_text(text, token->str);
               i=pos1+ token->len-1;
           }
           if (i == 0 && str1[i] >= 'A' && str1[i] <= 'z')
           {
               pos1 = i;
               token->len = size_word(str1 + pos1);
               token->str = (char*)calloc(token->len+1, sizeof(char));
               strncpy(token->str, str1 + pos1, token->len);
              // token->len = strlen(token->str);
               add_word(token, head);
              // printf("%s", token->str);
               add_to_text(text, token->str);
               i = pos1 + token->len - 1;
           }
          
   }
  /* for (int i = 0; i < (*text)->len; i++)
       printf("%s", (*text)->str[i]);*/
  // printf("\n");
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
   // char* vocabulary=(char*)calloc(1024,sizeof(char));
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
            // printf("%x - ", *head);
             // printf("%s", big_word.str);

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
                    //printf("%d", cnt);
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
                //if (size == 0)
                //{
                //    size++;
                //   // book = (glossary*)calloc(size, sizeof(glossary));
                //    book[size - 1].big = big_word;
                //    book[size - 1].small = small_word;
                //}
                //else
                //{
                //    book = (glossary*)realloc(book, ((size+1)*sizeof(glossary)));
                //    (book+size)->big = big_word;
                //    (book+size)->small = small_word;

                //    //book = add(book, size, big_word, small_word);
                //    size++;
                //}

                /*strcat(vocabulary, big_word.word.str);
                strcat(vocabulary, " ");
                strcat(vocabulary, small_word.word.str);
                strcat(vocabulary, "\n");*/
            }
        }
        else
            pop(head);
    }
   // for (int i = 0; i < size; i++)
   //     printf("%s - %s\n", book[i].big.word.str, book[i].small.word.str);
   //// printf("%s", vocabulary);

    create_new_file(book, size, file_name, text);


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
   // printf("%x\n", head);
    small.word.len = head->length;
    small.word.str = (char*)calloc(small.word.len, sizeof(char));
    small.word.str = head->word;
    small.count = head->count;
    profit = (big.count * big.word.len + small.count * small.word.len) - (big.count * small.word.len + small.count * big.word.len + big.word.len + small.word.len + 2);
    if (profit <= 0)
        return -1;
    else
        return profit;  
}

void create_new_file(glossary* book, int size, const char* file_name, string** text)
{
    FILE* file;
    FILE* file_compressed;
    WORD word;
    char* p;
    char* buffer = (char*)calloc(1024, sizeof(char));
    if ((file = fopen(file_name, "r+")) == NULL)
        exit(1);
    if ((file_compressed = fopen("Compressed.txt", "w+")) == NULL)
        exit(1);
    fseek(file_compressed, 0, SEEK_SET);
    fseek(file, 0, SEEK_SET);
    for (int i = 0; i < size; i++)
    {
        fputs(book[i].big.word.str, file_compressed);
        fputs("-", file_compressed);
        fputs(book[i].small.word.str, file_compressed);
        fputs("\n", file_compressed);
    }
    fputs("\0", file_compressed);
    for (int i = 0; i < size; i++)
    {
        swap_words(text, (book+i));
    }
    for (int i = 0; i < (*text)->len; i++)
    {
        fputs((*text)->str[i], file_compressed);
    }
    printf("Compression file - %d bytes", ftell(file_compressed));
   
  






    fclose(file);
    fclose(file_compressed);


}

void swap_words(string** text, glossary* word)
{
    
    for (int i = 0; i < (*text)->len; i++)
    {
        //printf("%s ", word->big.word.str);
        /*if ((*text)->str[i] == ' ' || (*text)->str[i] == '.' || (*text)->str[i] == ',' || (*text)->str[i] == '?' || (*text)->str[i] == '!' || (*text)->str[i] == '-' || (*text)->str[i] == '"')
            continue;*/
        //printf("%d", strlen((*text)->str[i]));
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

glossary *add(glossary* p, int n, WORD big_word, WORD small_word)
{
    
    int i = 0;
    glossary* temp = (glossary*)realloc(p, ((n + 1) * sizeof(glossary)));

    temp = temp + n;
    temp->big = big_word;
    temp->small = small_word;
    temp = temp - n;
    return temp;
}

void add_to_text(string** text, char* word)
{
    //printf("%s", word);
    //if ((*text)->len==0)
    //{
    //    //*text= (string*)calloc(1, sizeof(string));
    //    (*text)->len=1;
    //    (*text)->str = (char*)calloc(strlen(word), sizeof(char));
    //    (*text)->str = word;
    //}
    //else
    //{
    //    *text = (string*)realloc(*text,((*text)->len + 1)* sizeof(string));
    //    (*text)->str[(*text)->len] = (char*)calloc(strlen(word), sizeof(char));
    //    //strcpy((*text)->str[(*text)->len], word);
    //    (*text)->str[(*text)->len] = word;
    //    ((*text)->len)++;
    //}
    (*text)->str = realloc((*text)->str, ((*text)->len + 1) * sizeof(char*));
    (*text)->str[(*text)->len++] = word;

    


}

void loadingBar()
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