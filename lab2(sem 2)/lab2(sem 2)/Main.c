#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Header.h"

int main() {
	Word words[256];
	Dictionary dictionary[256];
	FILE* dictionaryFile = fopen("dictionary.txt", "w");
	int resFordictionaryFile;
	if ((resFordictionaryFile = fopen("dictionary.txt", "w")) == NULL) return 1;
	FILE* file = fopen("file.txt", "r+");
	int resForFire;
	if ((resForFire = fopen("file.txt", "r+")) == NULL) return 1;
	
	int allWordsCounter = getWordToStruct(words, dictionary, file);

	qsort(words, allWordsCounter, sizeof(words[0]), compare);
	int dictionaryCounter = wordsToDictionary(allWordsCounter, words, dictionary);

	for (int i = 0; i < dictionaryCounter; i++) {
		fprintf(dictionaryFile, "%s %s\n", dictionary[i].sourceName, dictionary[i].destinationName);
	}

	fclose(file);	
	file = fopen("file.txt", "r+");
	compressFile(file, dictionary, dictionaryCounter);
	fclose(file);

	fclose(dictionaryFile);
	printf("file if comprassed!");
}