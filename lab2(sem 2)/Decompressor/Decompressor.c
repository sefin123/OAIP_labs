#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Header.h"


void printMarks(char* str, int i, FILE* comprassFile) {
	switch (str[i]) {
	case ' ':
		fprintf(comprassFile, " ");
		break;
	case ',':
		fprintf(comprassFile, ",");
		break;
	case '.':
		fprintf(comprassFile, ".");
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

void deCompressFile(FILE* sourceFile, Dictionary* dictionary, int dictionaryCounter) {
	FILE* deCompressFile;
	char str[8192];
	int dictionaryIterator = 0;
	int wordIndex = 0;
	deCompressFile = fopen("decompressor.txt", "w");
	char* word = (char*)calloc(1, sizeof(char));
	while ((fgets(str, 8192, sourceFile)) != NULL) {
		for (int i = 0; i <= (strlen(str)); i++) {
			if (str[i] == ' ' || str[i] == '\0' || str[i] == '\n' || str[i] == ',' || str[i] == '.' || str[i] == ';' || str[i] == ':') {
				
				word[wordIndex] = '\0';
				
				for (dictionaryIterator = 0; dictionaryIterator < dictionaryCounter; dictionaryIterator++) {
					if (strcmp(dictionary[dictionaryIterator].destinationName, word) == 0) {
						fprintf(deCompressFile, "%s", dictionary[dictionaryIterator].sourceName);
						printMarks(str, i, deCompressFile);

						break;
					}
					else
						if (strcmp(dictionary[dictionaryIterator].sourceName, word) == 0) {
							fprintf(deCompressFile, "%s", dictionary[dictionaryIterator].destinationName);
							printMarks(str, i, deCompressFile);

							break;
						}
				}
				if (strcmp(dictionary[dictionaryIterator].destinationName, word) != 0 && strcmp(dictionary[dictionaryIterator].sourceName, word) != 0) {
					fprintf(deCompressFile, "%s", word);
					printMarks(str, i, deCompressFile);

				}
				wordIndex = 0;
			}
			else {
				word[wordIndex] = str[i];
				word = (char*)realloc(word, (wordIndex + 2) * sizeof(char));
				wordIndex++;
			}
		}
		fprintf(deCompressFile, "\n");
	}
	fclose(deCompressFile);
}

Dictionary* wordsFromDictionaryToStruct(FILE* file, int* dictionaryCounter) {
	Dictionary* dictionary = (Dictionary*) calloc(1,sizeof(Dictionary));
	int wordIndex = 0;
	char str[8192];
	char* word = (char*)calloc(1,sizeof(char));

	while ((fgets(str, 8192, file)) != NULL) {


		for (int i = 0; i < strlen(str); i++) {

			if (str[i] == ' ') {
				word[wordIndex] = '\0';
				strcpy(dictionary[*dictionaryCounter].sourceName, word);
				wordIndex = 0;

			}
			else if (str[i] == '\0' || str[i] == '\n') {
				word[wordIndex] = '\0';
				strcpy(dictionary[*dictionaryCounter].destinationName, word);
				wordIndex = 0;
			}
			else {
				word[wordIndex] = str[i];
				word = (char*)realloc(word, (wordIndex + 2) * sizeof(char));
				wordIndex++;
			}
		}
		*dictionaryCounter = *dictionaryCounter + 1;
		dictionary = (Dictionary*)realloc(dictionary, (*dictionaryCounter + 1) * sizeof(Dictionary));
	}
	return dictionary;
}

int main() {
	Dictionary* dictionary;
	FILE* file = fopen("dictionaryForDecompressor.txt", "r+");
	FILE* compressFile = fopen("fileForDecompressor.txt", "r+");

	int dictionaryCounter = 0;
    dictionary = wordsFromDictionaryToStruct(file, &dictionaryCounter);

	fclose(file);
	deCompressFile(compressFile, dictionary, dictionaryCounter);
	fclose(compressFile);

	printf("File is decompressed!");

	return 0;
}