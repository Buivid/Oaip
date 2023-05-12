#define BITMAP_H
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#pragma pack(push, 1)

typedef struct BMPHeader {
    unsigned char B;
    unsigned char M;
    unsigned int bmpSize;
    unsigned char unused[4];
    unsigned int dataOffset;
} BMPHeader;

typedef struct DIBHeader {
    unsigned int headerSize;
    int width;
    int height;
    unsigned short colorPlanes;
    unsigned short bitsPerPixel;
    unsigned int comp;
    unsigned int size;
    unsigned int pWidth;
    unsigned int pHeight;
    unsigned int colorPalette;
    unsigned int importantColors;
} DIBHeader;

#pragma pack(pop)

typedef struct Pixel {
    unsigned char b;
    unsigned char g;
    unsigned char r;
} Pixel;

typedef struct Palette {
    Pixel pixelPalette[16];
} Palette;

typedef struct BMPFile {
    BMPHeader* bmpHeader;
    DIBHeader* dibHeader;
    unsigned char* data;
} BMPFile;

//24bit
char* readFileName();
BMPFile* loadBMPFile(const char* filename);
void getData24(BMPFile* bmpFile, const char* filename);
Pixel* getPixel(BMPFile* bmpFile, int row, int col);
void writeBMPFile(BMPFile* bmpFile, const char* fileout);
void freeBMPFile(BMPFile* bmpFile);
//4bit
Palette getData4(BMPFile* bmpFile, const char* filename);
void convert4to24(BMPFile* bmpFile, Palette palette);
//filters
void invertColors(BMPFile* bmpFile);
void gammaCorrection(BMPFile* bmpFile);
void discoloration(BMPFile* bmpFile);
void medianFiltering(BMPFile* bmpFile);
