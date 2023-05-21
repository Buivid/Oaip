#define _CRT_SECURE_NO_WARNINGS
#include "func.h"


int main() {
    int choose = curcle();
    Node* root = NULL;
    while (choose != EXIT) {
        FILE* fp = fopen("database.txt", "r");
        if (fp == NULL) {
            printf("File not found or corrupted :(\n");
            _getch();
            exit(0);
        }
        root = read(fp);
        fclose(fp);
        if (choose == AKINATOR) {
            akinator(root);
            fp = fopen("database.txt", "w");
            if (fp == NULL) {
                printf("File not found or corrupted :(\n");
                _getch();
                exit(0);
            }
            save_tree(root, fp);
            fclose(fp);
        }
        else if (choose == BASE) {

            Leafs* leafs = malloc(sizeof(Leafs));
            leafs->element = (char**)malloc(sizeof(char*));
            leafs->count = 0;

            get_leaf_elements(root, leafs);

            for (int i = 0; i < leafs->count; i++) printf("%d: %s", i, leafs->element[i]);
            for (int i = leafs->count - 1; i >= 0; i--) free(leafs->element[i]);
            free(leafs->element);
            free(leafs);

            _getch();

        }

        choose = curcle();

    }

    free_tree(root);
    return 0;
}