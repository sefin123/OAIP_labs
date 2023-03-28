#pragma once
#include <stdbool.h>

typedef struct Word {
	char name[50];
	int size;
	int count;
	int value;
	bool isChanged;
} Word;


typedef struct Dictionary {
	char destinationName[50];
	char sourceName[50];
} Dictionary;

int findIndexByNameForWords(char* name, Word* words, int size);

int compare(Word a, Word b);

void printMarks(char* str, int i, FILE* comprassFile);

void compressFile(FILE* sourceFile, Dictionary* dictionary, int dictionaryCounter);

Word* getWordToStruct(int *allWordsCounter, FILE* file);

Dictionary* wordsToDictionary(int allWordsCounter, Word* words, int* dictionaryCounter);
