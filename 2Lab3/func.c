#define _CRT_SECURE_NO_WARNINGS
#include "func.h"

char* readFileName() {
    char* inpFileName = malloc(1);
    scanf("%99s", inpFileName);
    rewind(stdin);
    FILE* file = fopen(inpFileName, "rb");
    if (!file) {
        printf("File with this name does not exist! Try again\n");
        inpFileName = readFileName();
    }
    else fclose(file);
    return inpFileName;
}

BMPFile* loadBMPFile(const char* filename) {
    BMPFile* bmpFile = malloc(sizeof(BMPFile));
    BMPHeader* bmpHeader;
    DIBHeader* dibHeader;
    unsigned char* data = NULL;

    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Can't open file");
        exit(0);
    }

    bmpHeader = malloc(sizeof(BMPHeader));
    fread(bmpHeader, sizeof(BMPHeader), 1, file);

    if (bmpHeader->B == 'B' && bmpHeader->M == 'M') {
        dibHeader = malloc(sizeof(DIBHeader));
        fread(dibHeader, sizeof(DIBHeader), 1, file);
    }
    else {
        printf("Incorrect file format");
        fclose(file);
        exit(0);
    }
    fclose(file);

    bmpFile->bmpHeader = bmpHeader;
    bmpFile->dibHeader = dibHeader;
    bmpFile->data = data;

    return bmpFile;
}

void getData24(BMPFile* bmpFile, const char* filename) {

    int width = bmpFile->dibHeader->width;
    int height = bmpFile->dibHeader->height;
    int padding = 0;

    if ((width * 3) % 4 != 0) {
        padding = 4 - ((width * 3) % 4);
    }

    unsigned int offset = bmpFile->bmpHeader->dataOffset;

    FILE* file = fopen(filename, "rb");

    fseek(file, offset, SEEK_SET);
    unsigned char* data = malloc(width * height * 3);

    for (int row = 0; row < height; row++) {
        fread(&data[row * (width * 3)], sizeof(unsigned char) * 3, width, file);

        unsigned char paddingByte;
        for (int p = 0; p < padding; p++) {
            fread(&paddingByte, sizeof(unsigned char), 1, file);
        }
    }
    fclose(file);
    bmpFile->dibHeader->size = bmpFile->bmpHeader->bmpSize - bmpFile->bmpHeader->dataOffset;
    bmpFile->data = data;
}

Palette getData4(BMPFile* bmpFile, const char* filename) {
    Palette palette;
    FILE* file = fopen(filename, "rb");
    unsigned char paddingByte;
    unsigned int offset = bmpFile->dibHeader->headerSize + 14;
    unsigned char* data = malloc(bmpFile->bmpHeader->bmpSize - bmpFile->bmpHeader->dataOffset);
    fseek(file, offset, SEEK_SET);

    for (int i = 0; i < 16; i++) {
        fread(&palette.pixelPalette[i].b, sizeof(unsigned char), 1, file);
        fread(&palette.pixelPalette[i].g, sizeof(unsigned char), 1, file);
        fread(&palette.pixelPalette[i].r, sizeof(unsigned char), 1, file);
        fread(&paddingByte, sizeof(unsigned char), 1, file);
    }
    for (int i = 0; i < bmpFile->bmpHeader->bmpSize - bmpFile->bmpHeader->dataOffset; i++) {
        fread(&data[i], sizeof(unsigned char), 1, file);
    }
    bmpFile->data = data;
    fclose(file);
    return palette;
}

void convert4to24(BMPFile* bmpFile, Palette palette) {
    unsigned int newDataSize = bmpFile->dibHeader->width * bmpFile->dibHeader->height * 3;
    unsigned int dataSize = bmpFile->bmpHeader->bmpSize - bmpFile->bmpHeader->dataOffset;
    unsigned char* newData = malloc(newDataSize);
    unsigned int counter = 0;
    unsigned char* data = bmpFile->data;
    for (int i = 0; i < dataSize; i++) {
        int firstByte = data[i] / 16;
        int secondByte = data[i] % 16;
        newData[counter] = palette.pixelPalette[firstByte].b;
        counter++;
        newData[counter] = palette.pixelPalette[firstByte].g;
        counter++;
        newData[counter] = palette.pixelPalette[firstByte].r;
        counter++;
        newData[counter] = palette.pixelPalette[secondByte].b;
        counter++;
        newData[counter] = palette.pixelPalette[secondByte].g;
        counter++;
        newData[counter] = palette.pixelPalette[secondByte].r;
        counter++;
    }
    bmpFile->dibHeader->bitsPerPixel = 24;
    bmpFile->data = newData;
    bmpFile->dibHeader->size = newDataSize;
    bmpFile->bmpHeader->dataOffset = 54;
}

void writeBMPFile(BMPFile* bmpFile, const char* fileout) {
    FILE* file = fopen(fileout, "wb");
    int width = bmpFile->dibHeader->width;
    int height = bmpFile->dibHeader->height;

    int padding = 0;
    if ((width * 3) % 4 != 0) {
        padding = 4 - ((width * 3) % 4);
    }
    fwrite(bmpFile->bmpHeader, sizeof(BMPHeader), 1, file);
    fwrite(bmpFile->dibHeader, sizeof(DIBHeader), 1, file);

    unsigned char* data = bmpFile->data;
    for (int row = 0; row < height; row++) {
        fwrite(&data[row * (width * 3)], sizeof(unsigned char) * 3, width, file);

        for (int p = 0; p < padding; p++) {
            unsigned char null = 0;
            fwrite(&null, sizeof(unsigned char), 1, file);
        }
    }

    fclose(file);
}

void freeBMPFile(BMPFile* bmpFile) {
    if (bmpFile) {
        free(bmpFile->bmpHeader);
        free(bmpFile->dibHeader);
        free(bmpFile->data);
        free(bmpFile);
    }
}

Pixel* getPixel(BMPFile* bmpFile, int row, int col) {
    Pixel* pixel = NULL;
    int width = bmpFile->dibHeader->width;
    pixel = (Pixel*)&(bmpFile->data[row * (width * 3) + (col * 3)]);
    return pixel;
}


void invertColors(BMPFile* bmpFile) {
    int width = bmpFile->dibHeader->width;
    int height = bmpFile->dibHeader->height;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            Pixel* pixel = getPixel(bmpFile, row, col);

            pixel->b = ~(pixel->b);
            pixel->g = ~(pixel->g);
            pixel->r = ~(pixel->r);
        }
    }
}

void gammaCorrection(BMPFile* bmpFile) {
    float gamma;
    printf("Enter gamma coefficient: ");
    scanf("%f", &gamma);

    int width = bmpFile->dibHeader->width;
    int height = bmpFile->dibHeader->height;
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            Pixel* pixel = getPixel(bmpFile, row, col);

            pixel->b = pow(pixel->b / 255.0, gamma) * 255.0;
            pixel->g = pow(pixel->g / 255.0, gamma) * 255.0;
            pixel->r = pow(pixel->r / 255.0, gamma) * 255.0;
        }
    }
}

void discoloration(BMPFile* bmpFile) {
    int width = bmpFile->dibHeader->width;
    int height = bmpFile->dibHeader->height;
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            Pixel* pixel = getPixel(bmpFile, row, col);


            int param = 0.3 * pixel->r + 0.59 * pixel->g + 0.1 * pixel->b;
            pixel->b = param;
            pixel->g = param;
            pixel->r = param;
        }
    }
}


void medianFiltering(BMPFile* bmpFile) {
    Pixel* temp[9];
    int count;
    int width = bmpFile->dibHeader->width;
    int height = bmpFile->dibHeader->height;
    for (int i = 1; i < height - 1; i++) {
        for (int j = 1; j < width - 1; j++) {
            count = 0;
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    temp[count] = getPixel(bmpFile, i + k, j + l);
                    count++;
                }
            }
            for (int k = 0; k < 9; k++) {
                for (int l = k + 1; l < 9; l++) {
                    if (temp[k]->r > temp[l]->r) {
                        Pixel* tmPix = temp[k];
                        temp[k] = temp[l];
                        temp[l] = tmPix;
                    }
                }
            }

            Pixel* pixel = getPixel(bmpFile, i, j);
            pixel->r = temp[4]->r;
            pixel->g = temp[4]->g;
            pixel->b = temp[4]->b;

        }
    }
}