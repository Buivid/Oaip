#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "func.h"

int main() {
    char* outFileName;
    char* inpFileName;
    printf("Enter file name: ");
    inpFileName = readFileName();

    BMPFile* bmpFile = loadBMPFile(inpFileName);
    Palette palette;
    printf("\nBits per pixel %d", bmpFile->dibHeader->bitsPerPixel);
    if (bmpFile->dibHeader->bitsPerPixel == 4) {
        palette = getData4(bmpFile, inpFileName);
        convert4to24(bmpFile, palette);
    }
    else getData24(bmpFile, inpFileName);

    printf("\nChoose your image processing option: \n");
    while (1) {
        int choose;
        printf("1 -> Discoloration\n2 -> Invert colors\n3 -> Gamma correction\n4 -> Median filtering\n0 -> Finish and save the result\n");
        while (!scanf("%d", &choose) || choose > 4 || choose < 0 || getchar() != '\n') {
            printf("Wrong value! Try again:");
            rewind(stdin);
        }

        if (choose == 0)
            break;
        else if (choose == 1) {
            discoloration(bmpFile);
            writeBMPFile(bmpFile, "White&Black.bmp");
            system("cls");
            printf("Done.");

        }
        else if (choose == 2) {
            invertColors(bmpFile);
            writeBMPFile(bmpFile, "NIGGAtive.bmp");
            system("cls");
            printf("Done.");
        }
        else if (choose == 3) {
            gammaCorrection(bmpFile);
            writeBMPFile(bmpFile, "Gamma.bmp");
            system("cls");
            printf("Done.");
         
        }
        else if (choose == 4) {
            medianFiltering(bmpFile);
            writeBMPFile(bmpFile, "Mefedron.bmp");
            system("cls");
            printf("Done.");
       
        }
    
        printf("\n");

    }
    printf("\nFile saved");
    freeBMPFile(bmpFile);
    return 0;
}