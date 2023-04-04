#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct BmpHeader BmpHeader;
struct BmpHeader {
	uint32_t fileSize;
	uint8_t _space[4];
	uint32_t dataOffset;
	uint32_t infoHeaderSize;

	struct {
		uint32_t width, height;
	} size;

	uint16_t planeCount;
	uint16_t bitsPerPixel;
	uint32_t compressionType;
	uint32_t imageSize;

	struct {
		uint32_t width, height;
	} pixelDensity;

	uint32_t colorCount;
	uint32_t importantColorCount;
};

typedef struct Pixel Pixel;
struct Pixel {
	uint8_t blue, green, red;
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