#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Header.h"

int main() {
	char nameOfFile[256];
	printf("Enter file:");
	scanf("%s", nameOfFile);

	FILE* file = fopen(nameOfFile, "r");
	assert(file && "Cant open file");

	BmpFile bmpFile = readBMPFile(file);
	printHeader(&bmpFile.header);

	fclose(file);	

	menu(bmpFile);
	
	FILE* fileOutput = fopen("output.bmp","wb");
	
	fputs("BM", fileOutput);
	fwrite(&bmpFile.header, sizeof(bmpFile.header), 1, fileOutput);
	char zero = 0;
	while (ftell(fileOutput) < bmpFile.header.dataOffset) fwrite(&zero, 1, 1, fileOutput);
	fwrite(bmpFile.data, sizeof(*bmpFile.data), bmpFile.header.imageSize, fileOutput);

	destructBMPFile(&bmpFile);
}