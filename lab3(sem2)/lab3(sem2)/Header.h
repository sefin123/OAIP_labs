#pragma once
#include <stdio.h>
#include <stdlib.h>

#pragma pack(1)

typedef struct BMPHeader {
	unsigned char ID[2];
	unsigned int sizeFile;
	unsigned char unudsed[4];
	unsigned int pixelOffset;

} BMPHeader;

typedef struct DIBHeader {
	unsigned int sizeHeader;
	unsigned int width;
	unsigned int height;
	unsigned short colorPlanes;
	unsigned short bitPerPixel;
	unsigned int comp;
	unsigned int sizeData;
	unsigned int pwidth;
	unsigned int pheight;
	unsigned int countColor;
	unsigned int countImpColor;
}DIBHeader;

typedef struct BMPFile{
	BMPHeader bhdr;
	DIBHeader dhdr;
	unsigned char* data;
}BMPFile;

typedef struct pixelStruct {
	unsigned char blue;
	unsigned char green;
	unsigned char red;
}pixelStruct;

#pragma pop

void printParametrsOfFile(BMPFile* bmpFile);

BMPFile* loadReadBMPFile(char* name,FILE* file);

pixelStruct** readPixels(pixelStruct** pixel, BMPFile* bmpFile, FILE* file);

void freeBMPFile(BMPFile* bmpFile);

void negative(pixelStruct** pixel, BMPFile* bmpFile);