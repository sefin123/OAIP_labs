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
	char str[2048];
	int dictionaryIterator = 0;
	int wordIndex = 0;
	int destinationName = 0;
	deCompressFile = fopen("decompressor.txt", "w");
	char word[128];
	while ((fgets(str, 2048, sourceFile)) != NULL) {
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
				wordIndex++;
			}
		}
		fprintf(deCompressFile, "\n");
	}
	fclose(deCompressFile);
}

int wordsFromDictionaryToStruct(FILE* file, Dictionary* dictionary) {
	int wordIndex = 0;
	char str[256];
	int dictionaryCounter = 0;
	char word[256];

	while ((fgets(str, 256, file)) != NULL) {


		for (int i = 0; i < strlen(str); i++) {

			if (str[i] == ' ') {
				word[wordIndex] = '\0';
				strcpy(dictionary[dictionaryCounter].sourceName, word);
				wordIndex = 0;
				memset(word, 0, strlen(word));

			}
			else if (str[i] == '\0' || str[i] == '\n') {
				word[wordIndex] = '\0';
				strcpy(dictionary[dictionaryCounter].destinationName, word);
				wordIndex = 0;
				memset(word, 0, strlen(word));
			}
			else {
				word[wordIndex] = str[i];
				wordIndex++;
			}
		}
		dictionaryCounter++;
	}
	return dictionaryCounter;
}

int main() {
	Dictionary dictionary[256];
	FILE* file = fopen("dictionaryForDecompressor.txt", "r+");
	FILE* compressFile = fopen("fileForDecompressor.txt", "r+");

	int dictionaryCounter = 0;
	dictionaryCounter = wordsFromDictionaryToStruct(file, dictionary);

	fclose(file);
	deCompressFile(compressFile, dictionary, dictionaryCounter);
	fclose(compressFile);

	printf("File is decompressed!");

	return 0;
}