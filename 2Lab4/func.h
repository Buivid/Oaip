#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>


typedef struct Node {

    char* question;
    struct Node* yes;
    struct Node* no;

}Node;

typedef enum menu {

    EXIT,
    AKINATOR,
    BASE

}menu;

typedef struct Path {

    char** question;
    char** answer;
    int count;

}Path;

typedef struct Leafs {

    char** element;
    int count;

}Leafs;

int curcle();

Node* read(FILE* file);

Node* create_node(char* input);

void free_tree(Node* node);

void save_tree(Node* node, FILE* file);

void akinator(Node* node);

void get_leaf_elements(const Node* root, Leafs* leafs);

void reverse_akinator(const Node* node);