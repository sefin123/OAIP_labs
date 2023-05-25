#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Header.h"
#define fileName 256

int main() {
	char nameOfFile[fileName];
	printf("Enter file:");
	(void)scanf("%s", nameOfFile);

	nameOfFile[strlen(nameOfFile)] = '\0';
	
	FILE* file = fopen(nameOfFile, "r");
	assert(file && "Cant open file");

	BmpFile bmpFile = readBMPFile(file);
	printHeader(&bmpFile.header);

	fclose(file);	

	menu(bmpFile);
	
	FILE* fileOutput = fopen("output.bmp","wb");
	
	fputs("BM", fileOutput);
	fwrite(&bmpFile.header, sizeof(bmpFile.header), 1, fileOutput);

	fwrite(bmpFile.data, sizeof(*bmpFile.data), bmpFile.header.imageSize, fileOutput);

	destructBMPFile(&bmpFile);
}