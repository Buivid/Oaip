#pragma once
void check_input(int* choice);
void check_size(int* size);
void *memory(int row, int col);
void free_matrix(int** mas, int row);
//void memory(int*** mas, int row, int col, int k);
void input_matrix(int **mas, int  row, int col, int choice);
void hand_input(int** mas, int row, int col);
void random_input(int** mas, int row, int col);
void output_matrix(int **mas,int row,int col);
int cnt_even_element(int** mas, int length, int r);
void insertion_sort(int** mas, int row, int col);
void sort(int** mas, int row, int col);
