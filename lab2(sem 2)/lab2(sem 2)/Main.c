#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Header.h"

int main() {
	Word *words;
	Dictionary* dictionary;
	FILE* dictionaryFile = fopen("dictionary.txt", "w");
	FILE* file = fopen("file.txt", "r");
	int  allWordsCounter = 0;
	words = getWordToStruct(&allWordsCounter, file);

	qsort(words, allWordsCounter, sizeof(words[0]), compare);

	int dictionaryCounter = 0;
	dictionary = wordsToDictionary(allWordsCounter, words, &dictionaryCounter);
	
	for (int i = 0; i < dictionaryCounter; i++) {
		fprintf(dictionaryFile, "%s %s\n", dictionary[i].sourceName, dictionary[i].destinationName);
	}

	fclose(file);	
	file = fopen("file.txt", "r+");
	compressFile(file, dictionary, dictionaryCounter);
	fclose(file);

	fclose(dictionaryFile);
	printf("file if comprassed!");
	return 0;
}