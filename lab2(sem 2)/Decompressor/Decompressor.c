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
	FILE* comprassFile;
	char* str = calloc(256, sizeof(char));
	int wordIndex = 0;
	comprassFile = fopen("decompress.txt", "w");
	while ((fgets(str, 256, sourceFile)) != NULL) {
		int dictionaryIterator = 0;
		char* word = malloc(256 * sizeof(char));
		for (int i = 0; i <= (strlen(str)); i++) {
			if (str[i] == ' ' || str[i] == '\0' || str[i] == '\n') {
				printMarks(str, i, comprassFile);
				word[wordIndex] = '\0';
				for (int dictionaryIterator = 0; dictionaryIterator < dictionaryCounter; dictionaryIterator++) {
					if (strcmp(dictionary[dictionaryIterator].destinationName, word) == 0) {
						fprintf(comprassFile, "%s", dictionary[dictionaryIterator].sourceName);
						break;
					}
					else
						if (strcmp(dictionary[dictionaryIterator].sourceName, word) == 0) {
							fprintf(comprassFile, "%s", dictionary[dictionaryIterator].destinationName);
							break;
						}
						else
						{
							fprintf(comprassFile, "%s", word);
							break;
						}

				}
				wordIndex = 0;
			}
			else {
				word[wordIndex] = str[i];
				wordIndex++;
			}
		}
		fprintf(comprassFile, "\n");
	}
	fclose(comprassFile);
}

int main() {
	Dictionary dictionary[256];
	char stringInFile[256];
	FILE* file = fopen("dictionary.txt", "r+");
	FILE* compressFile = fopen("file.txt", "r+");

	int dictionaryCounter = 0;
	
	while ((fgets(stringInFile, 256, file)) != NULL) {

		char word[256];
		int wordIndex = 0;

		for (int i = 0; i < strlen(stringInFile); i++) {

			if (stringInFile[i] == ' ') {
				word[wordIndex] = '\0';
				strcpy(dictionary[dictionaryCounter].sourceName, word);
				wordIndex = 0;
				memset(word, 0, strlen(word));

			}
			else if (stringInFile[i] == '\0' || stringInFile[i] == '\n') {
				word[wordIndex] = '\0';
				strcpy(dictionary[dictionaryCounter].destinationName, word);
				wordIndex = 0;
				memset(word, 0, strlen(word));
			}
			else {
				word[wordIndex] = stringInFile[i];
				wordIndex++;
			}
		}
		dictionaryCounter++;
	}	
	fclose(file);
	deCompressFile(compressFile, dictionary, dictionaryCounter);
	fclose(compressFile);



	return 0;
}