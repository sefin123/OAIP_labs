#include <stdio.h>
#include <stdlib.h>
#include "Header.h"


int main() {

	struct word *word = calloc(1, sizeof(word));
	char list[30];

	FILE* file;
	int res = fopen_s(&file, "file.txt", "r+");
	if (res == NULL) printf("file is open\n");
	else printf("file isnt open\n");
	char *str = calloc(30,sizeof(char));
	fgets(str, 30, file);

	printf("%s\n", str);
	fclose(file);
	if ((fclose(file)) != NULL) printf("file is close");
	else printf("file isnt close");
	return 0;
}