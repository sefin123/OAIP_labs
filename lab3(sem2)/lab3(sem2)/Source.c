#include <stdio.h>
#include <stdlib.h>
#include "Header.h"


BMPFile* loadBMPFile(char* name) {
	FILE* file = fopen(name, "r");
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
	
	fclose(file);
	return bmpFile;
}

void freeBMPFile(BMPFile* bmpFile) {
	if (bmpFile) {
		free(bmpFile);
	}
}