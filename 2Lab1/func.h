#pragma once
enum st { IN, OUT };
typedef struct vacuum
{
	char* producer;
    enum st status;
	float price;
}vacuum;
vacuum* create();

void menu_correct(int* task);
void choice_continue(int* num);
void delete_menu();
void correct_choice_delete(int* num, int size);
void delete_element(vacuum** mas, int number, int* size);
void sort_one_field(vacuum* array, int size);
int variant_of_sort(int field, int counter, vacuum* mas);
int add(vacuum* p, int n);
int add_menu();
void view(vacuum* p, int* n);
int save(char* filename, vacuum* p, int n);
vacuum* load(char* filename);
int count(char* filename);
void view_menu();
void sort_one_field_menu();
int change_need(const char* str1, const char* str2);
int delete(vacuum* array, int k, int* size);