#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Header.h"


int findIndexByNameForWords(char* name, Word* words, int size) {
	for (int i = 0; i < size; i++) {
		if (!strcmp(words[i].name, name)) return i;
	}
	return -1;
}



int compare(Word a, Word b) {
	return a.size - b.size;
}

void printMarks(char* str, int i, FILE* comprassFile) {
	switch (str[i]) {
	case '.':
		fprintf(comprassFile, ".");
		break;
	case ',':
		fprintf(comprassFile, ",");
		break;
	case ' ':
		fprintf(comprassFile, " ");
		break;
	case '-':
		fprintf(comprassFile, "-");
	case ':':
		fprintf(comprassFile, ":");
		break;
	case ';':
		fprintf(comprassFile, ";");
		break;
	}
}

void compressFile(FILE* sourceFile, Dictionary* dictionary, int dictionaryCounter) {
	FILE* comprassFile;
	char str[8192];
	int dictionaryIterator = 0;
	int wordIndex = 0;
	int destinationName = 0;
	comprassFile = fopen("FileAftercomprass.txt", "w");
	//char word[128];
	char *word = (char*) calloc(1,sizeof(char));
	while ((fgets(str, 8192, sourceFile)) != NULL) {
		for (int i = 0; i <= (strlen(str)); i++) {
			if (str[i] == ' ' || str[i] == '\0' || str[i] == '\n' || str[i] == ',' || str[i] == '.' || str[i] == ';' || str[i] == ':') {
				word[wordIndex] = '\0';
				for (dictionaryIterator = 0; dictionaryIterator < dictionaryCounter; dictionaryIterator++) {
					if (strcmp(dictionary[dictionaryIterator].destinationName, word) == 0) {
						fprintf(comprassFile, "%s", dictionary[dictionaryIterator].sourceName);
						printMarks(str, i, comprassFile);
						break;
					}
					else
						if (strcmp(dictionary[dictionaryIterator].sourceName, word) == 0) {
							fprintf(comprassFile, "%s", dictionary[dictionaryIterator].destinationName);
							printMarks(str, i, comprassFile);
							break;
						}
				}
				if (strcmp(dictionary[dictionaryIterator].destinationName, word) != 0 && strcmp(dictionary[dictionaryIterator].sourceName, word) != 0) {
					fprintf(comprassFile, "%s", word);
					printMarks(str, i, comprassFile);
				}
				wordIndex = 0;
			}
			else {
				word[wordIndex] = str[i];
				word =(char*) realloc(word,(wordIndex + 1) * sizeof(char));
				wordIndex++;
			}
		}
		fprintf(comprassFile, "\n");
	}
	fclose(comprassFile);
}

int getWordToStruct(Word* words, Dictionary* dictionary, FILE* file) {
	char *str=(char*)malloc(8192);
	int allWordsCounter = 0;
	int wordIndex = 0;
	//char word[256];
	char *word =(char*) calloc(1,sizeof(char));
	while ((fgets(str, 8192, file)) != NULL)
	{
		for (int i = 0; i <= (strlen(str)); i++)
		{
			if (str[i] == ' ' || str[i] == '\0' || str[i] == '\n' || str[i] == ',' || str[i] == '.' || str[i] == ';' || str[i] == ':')
			{
				word[wordIndex] = '\0';

			     wordIndex = findIndexByNameForWords(word, words, allWordsCounter);
				if (wordIndex == -1) {
					strcpy(words[allWordsCounter].name, word);
					words[allWordsCounter].size = strlen(word);
					words[allWordsCounter].count = 1;
					words[allWordsCounter].isChanged = false;
					words[allWordsCounter].value = strlen(word);
					allWordsCounter++;
					words = (Word*)realloc(words, (allWordsCounter + 1) * sizeof(Word));
				}
				else {
					words[wordIndex].count = words[wordIndex].count + 1;
					words[wordIndex].value = words[wordIndex].value + strlen(word);
				}
				wordIndex = 0;
			}
			else
			{
				word[wordIndex] = str[i];
				if (word == NULL) return 1;
				word = (char*) realloc(word, (wordIndex + 2) * sizeof(char));
				wordIndex++;
			}
		}
	}
	return allWordsCounter;
}

int wordsToDictionary(int allWordsCounter, Word* words, Dictionary* dictionary) {
	int dictionaryCounter = 0;
	for (int i = 0; i < allWordsCounter; i++) {
		if (words[i].isChanged) continue;

		for (int j = 1; j < allWordsCounter; j++) {
			if (words[j].isChanged) continue;

			if (words[i].size != 0 && words[i].count > 1 && (words[i].value + words[j].value) > ((words[i].size * words[j].count) + (words[j].size * words[i].count))) {

				strcpy(dictionary[dictionaryCounter].sourceName, words[i].name);
				strcpy(dictionary[dictionaryCounter].destinationName, words[j].name);

				dictionaryCounter++;
				dictionary = (Dictionary*)realloc(dictionary, (dictionaryCounter + 1) * sizeof(Dictionary));

				words[i].isChanged = true;
				words[j].isChanged = true;
				break;
			}
		}
	}
	return dictionaryCounter;
}