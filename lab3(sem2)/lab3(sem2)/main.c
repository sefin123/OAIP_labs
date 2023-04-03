#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main() {
	printf("Enter file:");
	char *nameOfFile = malloc(256);
	scanf("%s",nameOfFile);
	FILE* file = NULL;
	BMPFile* bmpFile = loadReadBMPFile(nameOfFile,file);
	pixelStruct** pixel = NULL;
	pixel = readPixels(pixel, bmpFile, file);
	
	printParametrsOfFile(bmpFile);
	negative(pixel,bmpFile);
	
	freeBMPFile(bmpFile);

	FILE* fileOutput = fopen("output.bmp","wb");

	fwrite(&bmpFile->bhdr, sizeof(BMPHeader), 1, fileOutput);
	fwrite(&bmpFile->dhdr, sizeof(DIBHeader), 1, fileOutput);

	for (int i = 0; i < bmpFile->dhdr.height; i++) {
		for (int j = 0; j < bmpFile->dhdr.width; j++) {
			fwrite(&pixel[i][j], sizeof(pixelStruct), 1, fileOutput);
		}
	}

	return 0;
}