#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main() {
	printf("Enter file:");
	char nameOfFile[20];
	scanf("%s",nameOfFile);

	BMPFile* file = loadBMPFile(nameOfFile);
	printf(" ID %c%c \n sizeFile %d \n pixelOffset %d\n",file->bhdr.ID[0], file->bhdr.ID[1],file->bhdr.sizeFile,file->bhdr.pixelOffset);
	printf("\n sizeHeader %d\n width %d\n height %d\n colorPlanes %d\n bitPerPixel %d\n comp %d\n sizeData %d\n pwidth %d\n pheight %d\n countColor %d\n countImpColor %d\n ",
    file->dhdr.sizeHeader, file->dhdr.width, file->dhdr.height, file->dhdr.colorPlanes, file->dhdr.bitPerPixel,
    file->dhdr.comp,file->dhdr.sizeData, file->dhdr.pwidth, file->dhdr.pheight, file->dhdr.countColor, file->dhdr.countImpColor);
	for (int i = 0; i < file->dhdr.sizeData; i++) {
		if (i % 16 == 0)
			printf("\n%04x: ", i);
		printf("%02x ", file->data[i]);
	}
	freeBMPFile(file);

	return 0;
}