#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <math.h>
#include "Header.h"


BmpFile readBMPFile(FILE* file) {
	BmpFile bmpFile = {0};

	char signature[3] = {0};
	fread(signature, sizeof(*signature), 2, file);
	assert(strcmp(signature, "BM") == 0);

	fread(&bmpFile.header, sizeof(bmpFile.header), 1, file);

	bmpFile.data = calloc(bmpFile.header.imageSize, sizeof(*bmpFile.data));
	
	assert(bmpFile.header.bitsPerPixel == 24);
	fseek(file, bmpFile.header.dataOffset, SEEK_SET);
	fread(bmpFile.data, sizeof(*bmpFile.data), bmpFile.header.imageSize, file);

	return bmpFile;
}

void printHeader(BmpHeader* header) {
	printf("File size:  %d\n", header->fileSize);
	printf("Offset:     %d\n", header->dataOffset);
	printf("Width:      %d\n", header->size.width);
	printf("Height:     %d\n", header->size.height);
	printf("Bits/pixel: %d\n", header->bitsPerPixel);
	printf("Image size: %d\n", header->imageSize);
}

void negative(Pixel* pixel, int size) {
	for (int i = 0; i < size; i++)
	{
		pixel[i].blue = 255 - pixel[i].blue;
		pixel[i].red = 255 - pixel[i].red;
		pixel[i].green = 255 - pixel[i].green;
	}
}

void monoChrome(Pixel* pixel, int size) {

	for (int i = 0; i < size; i++) {
		//unsigned char brightness = (pixel[i].blue + pixel[i].blue + pixel[i].blue) / 3;
		char brightness = (char)(0.3 * pixel[i].red + 0.59 * pixel[i].green + 0.11 * pixel[i].blue);
		pixel[i].red = brightness;
		pixel[i].green = brightness;
		pixel[i].blue = brightness;
	}
}

void gammaCorection(Pixel* pixel, int size) {
	float correctionValue;
	
	printf("Value gamma corection: ");
	scanf("%f", &correctionValue);

	for (int i = 0; i < size; i++) {
		unsigned char red = 255 * pow(pixel[i].red / 255.0f, correctionValue);
		unsigned char green = 255 * pow(pixel[i].green / 255.0f, correctionValue);
		unsigned char blue = 255 * pow(pixel[i].blue / 255.0f, correctionValue);

		pixel[i].red = red;
		pixel[i].green = green;
		pixel[i].blue = blue;

	}
}

int byRed(Pixel* left, Pixel* right) {
	return right->red - left->red;
}

int byGreen(Pixel* left, Pixel* right) {
	return right->green - left->green;
}

int byBlue(Pixel* left, Pixel* right) {
	return right->blue - left->blue;
}

void blur(Pixel* pixels,int height,int width) {
	int radius;
	printf("enter blur radius: ");
	scanf("%d", &radius);

	const int surroundingSize = pow(2 * radius + 1, 2);
	const int median = surroundingSize / 2;
	const Pixel* surrounding = _malloca(sizeof(*surrounding) * surroundingSize);

	if (!surrounding) abort();

	for (int y = radius; y < height - radius; y++)
	{
		for (int x = radius; x < width - radius; x++)
		{
			Pixel* it = surrounding;
			for (int w = -radius; w <= radius; w++)
			{
				for (int h = -radius; h <= radius; h++)
				{
					*(it++) = pixels[(x + h) + (y + w) * width];
				}
			}

			Pixel* target = &pixels[x + y * width];

			qsort(surrounding, surroundingSize, sizeof(*surrounding), byRed);
			target->red = surrounding[median].red;

			qsort(surrounding, surroundingSize, sizeof(*surrounding), byGreen);
			target->green = surrounding[median].green;

			qsort(surrounding, surroundingSize, sizeof(*surrounding), byBlue);
			target->blue = surrounding[median].blue;
		}
	}
}

void menu(BmpFile bmpFile) {
	int menu;
	printf("select what u wanna do\n");
	printf("1. negative\n");
	printf("2. monoChrome\n");
	printf("3. gamma corection\n");
	printf("4. blur\n");
	printf("choose: ");
	scanf_s("%d",&menu);
	if (menu == 1) negative(bmpFile.data, bmpFile.header.imageSize);
	if (menu == 2) monoChrome(bmpFile.data, bmpFile.header.imageSize);
	if (menu == 3) gammaCorection(bmpFile.data, bmpFile.header.imageSize);
	if (menu == 4) blur(bmpFile.data, bmpFile.header.size.height, bmpFile.header.size.width);
}

void destructBMPFile(BmpFile* bmpFile) {
	if (!bmpFile) return;

	free(bmpFile->data);
}