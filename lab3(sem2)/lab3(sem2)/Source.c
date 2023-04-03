#include <stdio.h>
#include <stdlib.h>
#include "Header.h"


BMPFile* loadReadBMPFile(char* name,FILE* file) {
	file = fopen(name, "r");
	if (!file) {
		printf("Cant load file");
		exit(0);
	}
	BMPFile* bmpFile = (BMPFile*)malloc(sizeof(BMPFile));
	fread(&bmpFile->bhdr, sizeof(BMPHeader), 1, file);
	fread(&bmpFile->dhdr, sizeof(DIBHeader), 1, file);

	bmpFile->data = (unsigned char*) malloc(bmpFile->dhdr.sizeData);
	fseek(file, bmpFile->bhdr.pixelOffset, SEEK_SET);
	fread(bmpFile->data, bmpFile->dhdr.sizeData, 1, file);

	if (bmpFile->bhdr.ID[0] != 'B' || bmpFile->bhdr.ID[1] != 'M') {
		printf("not BMP file");
	}

	/*pixel = malloc(sizeof(pixelStruct*) * bmpFile->dhdr.height);

	for (int i = 0; i < bmpFile->dhdr.height; i++) {
		pixel[i] = malloc(sizeof(pixelStruct) * bmpFile->dhdr.width);
	}
	
	for (int i = 0; i < bmpFile->dhdr.height; i++) {
		for (int j = 0; j < bmpFile->dhdr.width; j++) {
			char px = &pixel[i][j];
			fread(px, sizeof(pixelStruct), 1, file);
		}
	}*/

	return bmpFile;
}

pixelStruct** readPixels(pixelStruct** pixel,BMPFile* bmpFile,FILE* file) {

	pixel = malloc(sizeof(pixelStruct*) * bmpFile->dhdr.height);

	for (int i = 0; i < bmpFile->dhdr.height; i++) {
		pixel[i] = malloc(sizeof(pixelStruct) * bmpFile->dhdr.width);
	}

	for (int i = 0; i < bmpFile->dhdr.height; i++) {
		for (int j = 0; j < bmpFile->dhdr.width; j++) {
			fread(&pixel[i][j], sizeof(pixelStruct), 1, file);
		}
	}
	fclose(file);
	return pixel;
}

void printParametrsOfFile(BMPFile* bmpFile) {
	printf(" ID %c%c \n sizeFile %d \n pixelOffset %d\n", bmpFile->bhdr.ID[0], bmpFile->bhdr.ID[1], bmpFile->bhdr.sizeFile, bmpFile->bhdr.pixelOffset);
	printf("\n sizeHeader %d\n width %d\n height %d\n colorPlanes %d\n bitPerPixel %d\n comp %d\n sizeData %d\n pwidth %d\n pheight %d\n countColor %d\n countImpColor %d\n ",
		bmpFile->dhdr.sizeHeader, bmpFile->dhdr.width, bmpFile->dhdr.height, bmpFile->dhdr.colorPlanes, bmpFile->dhdr.bitPerPixel,
		bmpFile->dhdr.comp, bmpFile->dhdr.sizeData, bmpFile->dhdr.pwidth, bmpFile->dhdr.pheight, bmpFile->dhdr.countColor, bmpFile->dhdr.countImpColor);

}

void negative(pixelStruct** pixel,BMPFile* bmpFile) {

	for (int i = 0; i < bmpFile->dhdr.height; i++) {
		for (int j = 0; j < bmpFile->dhdr.width; j++) {

			char px = &pixel[i][j];
			pixel[i][j].blue = 255 - pixel[i][j].blue;
			pixel[i][j].red = 255 - pixel[i][j].red;
			pixel[i][j].green = 255 - pixel[i][j].green;
		}
	}

}

void freeBMPFile(BMPFile* bmpFile) {
	if (bmpFile) {
		free(bmpFile);
	}
}