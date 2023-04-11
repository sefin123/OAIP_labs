#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct BmpHeader BmpHeader;
struct BmpHeader {
	unsigned int fileSize;
	unsigned char space[4];
	unsigned int dataOffset;
	unsigned int infoHeaderSize;

	struct {
		unsigned int width, height;
	} size;

	unsigned short planeCount;
	unsigned short bitsPerPixel;
	unsigned int compressionType;
	unsigned int imageSize;

	struct {
		unsigned int width, height;
	} pixelDensity;

	unsigned int colorCount;
	unsigned int importantColorCount;
};

typedef struct Pixel Pixel;
struct Pixel {
	unsigned char blue, green, red;
};

typedef struct BmpFile BmpFile;
struct BmpFile {
	BmpHeader header;
	Pixel* data;
};

void printHeader(BmpHeader* header);

BmpFile readBMPFile(FILE* file);

void destructBMPFile(BmpFile* bmpFile);

void negative(Pixel* arr, int size);

void menu(BmpFile bmpFile);