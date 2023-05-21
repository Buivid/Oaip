#define _CRT_SECURE_NO_WARNINGS
#include "func.h"

char* get_str() {

    int length = 1;
    char* string = (char*)malloc(length * sizeof(char));
    for (int i = 0;; i++) {
        string[i] = (char)getchar();
        if (string[i] == '\n') 
        {
            string[i] = '\0';
            break;
        }
        length++;
        string = (char*)realloc(string, length);
    }

    return string;

}

Node* create_node(char* input) {

    Node* node = (Node*)malloc(sizeof(Node));

    node->question = _strdup(input);
    node->yes = NULL;
    node->no = NULL;

    return node;

}

void akinator(Node* node) {

    printf("Answer the questions below to get prediction.\n\n");
    printf("%s\n", node->question);
    char* answer = get_str();
    while (strcmp(answer, "yes") != 0 && strcmp(answer, "no") != 0) {
        printf("Input \"yes\" or \"no\"\n");
        rewind(stdin);
        answer = get_str();
    }
    system("cls");
    if (strcmp(answer, "yes") == 0) {
        if (node->yes == NULL) {
            printf("I guessed it! :)\n");
            free(answer);
            _getch();
        }
        else {
            free(answer);
            akinator(node->yes);
        }
    }
    else {
        free(answer);
        if (node->no == NULL) {
            printf("Sorry, I can't guess...\nWho is your person?\n");
            char* new_object = get_str();
            printf("What is a question that distinguishes %s from %s?\n", new_object, node->question);
            char* new_question = get_str();
            new_question = realloc(new_question, strlen(new_question) + 1);
            strcat(new_question, "\n");
            printf("What is the answer to the question for %s?\n", new_object);
            char* new_answer = get_str();
            Node* new_node = create_node(new_question);
            new_object = realloc(new_object, strlen(new_object) + 1);
            strcat(new_object, "\n");
            if (strcmp(new_answer, "yes") == 0) {
                new_node->yes = create_node(new_object);
                new_node->no = create_node(node->question);
            }
            else {
                new_node->yes = create_node(node->question);
                new_node->no = create_node(new_object);
            }
            memcpy(node, new_node, sizeof(Node));
        }
        else akinator(node->no);
    }
}

void get_leaf_elements(const Node* root, Leafs* leafs) {

    if (root == NULL) return;

    if (root->no == NULL && root->yes == NULL) {
        leafs->element = realloc(leafs->element, (leafs->count + 1) * sizeof(char*));
        leafs->element[leafs->count++] = _strdup(root->question);
    }
    else {
        get_leaf_elements(root->yes, leafs);
        get_leaf_elements(root->no, leafs);
    }

}

void remember_path(const Node* root, char* key, Path* path, int* len) {

    if (root == NULL) *len = 0;
    else if (strcmp(root->question, key) == 0 && root->yes == NULL && root->no == NULL) {

        path->count = *len;
        path->question = realloc(path->question, (path->count + 1) * sizeof(char*));
        path->answer = realloc(path->answer, (path->count + 1) * sizeof(char*));

        path->question[path->count] = _strdup(root->question);
        path->answer[path->count] = _strdup("yes");
        (*len)++;

    }
    else {
        remember_path(root->no, key, path, len);
        if (*len > 0) {

            path->count = *len;
            path->question = realloc(path->question, (path->count + 1) * sizeof(char*));
            path->answer = realloc(path->answer, (path->count + 1) * sizeof(char*));

            path->question[path->count] = _strdup(root->question);
            path->answer[path->count] = _strdup("no");
            (*len)++;

        }
        else {
            remember_path(root->yes, key, path, len);
            if (*len > 0) {

                path->count = *len;
                path->question = realloc(path->question, (path->count + 1) * sizeof(char*));
                path->answer = realloc(path->answer, (path->count + 1) * sizeof(char*));

                path->question[path->count] = _strdup(root->question);
                path->answer[path->count] = _strdup("yes");

                (*len)++;

            }
        }
    }

}

void free_tree(Node* node) {

    if (node != NULL) {
        if (node->no != NULL) free_tree(node->no);
        if (node->yes != NULL) free_tree(node->yes);
        free(node);
    }

}

Node* read(FILE* file) {

    char question[100];
    fgets(question, sizeof(question), file);
    if (question[0] == '#') return NULL;

    Node* node = create_node(question);
    node->yes = read(file);
    node->no = read(file);

    return node;

}

void save_tree(Node* node, FILE* file) {

    if (node == NULL) {

        fprintf(file, "#\n");
        return;

    }

    fprintf(file, "%s", node->question);
    save_tree(node->yes, file);
    save_tree(node->no, file);

}

int curcle() {

    int choose;

    system("cls");

    printf("0. Exit\n");
    printf("1. Akinator\n");
    printf("2. Show base\n");
    printf("Your answer: ");

    while (scanf_s("%d", &choose) != 1 || choose < 0 || choose > 3 || getchar() != '\n') {
        printf("Error! Try again...\n");
        rewind(stdin);
    }
    system("cls");

    return choose;

}