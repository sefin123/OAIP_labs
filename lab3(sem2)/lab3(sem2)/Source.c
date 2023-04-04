#include <stdio.h>
#include <stdlib.h>
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
		unsigned char brightness = (pixel[i].blue + pixel[i].blue + pixel[i].blue) / 3;
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

int compare(int iterator, char* l, char* r) {
	if (l[iterator] >= r[iterator]) {
		return 1;
	}
	return -1;
}

Pixel* getPixel(int x, int y, BmpHeader* bmpFile)
{
	if (x < 0) x = 0;
	else if (x >= bmpFile->size.width) x = bmpFile->size.width - 1;

	if (y < 0) y = 0;
	else if (y >= bmpFile->size.height) y = bmpFile->size.height - 1;

	return /*(Pixel*)context->pixels->buffer + */
		(Pixel*)((y * bmpFile->size.width) + x);
}

Pixel findMedian(Pixel* pixels,int size) {
	Pixel median;

	qsort(pixels, size, sizeof(Pixel), compare, 0);
	median.red = pixels[size / 2].red;

	qsort(pixels, size, sizeof(Pixel), compare, 1);
	median.green = pixels[size / 2].green;
	
	qsort(pixels, size, sizeof(Pixel), compare, 2);
	median.blue = pixels[size / 2].blue;

	return median;
}

void blurFilter(Pixel* pixel,BmpHeader* bmpFile, int x, int y) {
	Pixel pixels[9];

	for (int i = -1; i <= 1; i++)
	{
		pixels[i + 1] = *getPixel(x + i, y + 1, bmpFile);
		pixels[3 + i + 1] = *getPixel(x + i, y, bmpFile);
		pixels[5 + i + 1] = *getPixel(x + i, y - 1, bmpFile);
	}
	
	*pixel = findMedian(pixels, sizeof(pixels) / sizeof(Pixel));
	//*context->resultPixel = findMedian(pixels, sizeof(pixels) / sizeof(Pixel));
	//context->resultPixel->a = context->pixel->a;
}

void blur(Pixel* pixel, BmpHeader* bmpFile) {

	for (int y = 0; y < bmpFile->size.height; y++) {
		for (int x = 0; x < bmpFile->size.width; x++) {

			blurFilter(pixel, bmpFile, x, y);

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
	if (menu == 1) negative(bmpFile.data, bmpFile.header.imageSize);;
	if (menu == 2) monoChrome(bmpFile.data, bmpFile.header.imageSize);
	if (menu == 3) gammaCorection(bmpFile.data, bmpFile.header.imageSize);
	if (menu == 4) blur(bmpFile.data, &bmpFile);
}

void destructBMPFile(BmpFile* bmpFile) {
	if (!bmpFile) return;

	free(bmpFile->data);
}