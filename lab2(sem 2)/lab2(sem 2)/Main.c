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

//слов должно быть больше одного
//

void printMarks(char* str,int i,FILE* comprassFile) {
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

void compressFile(FILE* sourceFile, Dictionary* dictionary, int dictionaryCounter) {
	FILE* comprassFile;
	char* str = calloc(256, sizeof(char));
	int wordIndex = 0;
	comprassFile = fopen("comprass.txt", "w");
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
					} else
					if (strcmp(dictionary[dictionaryIterator].sourceName, word) == 0) {
						fprintf(comprassFile, "%s", dictionary[dictionaryIterator].destinationName);
						break;
					}else
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

// Если равно sourceNmae => меняем на destinationName
	// Если равно destinationName => меняем на sourceNmae
	// Если не равно ничему => оставялем




int main() {
	Word words[256];
	Dictionary dictionary[256];
	char stringInFile[256];
	FILE* file = fopen("file.txt", "r+");
	FILE* dictionaryFile = fopen("dictionary.txt", "w");
	
	int allWordsCounter = 0;
	int stringIndex = 0;
	while ((fgets(stringInFile, 256, file)) != NULL)
	{
		char word[256];
		for (int i = 0; i <= (strlen(stringInFile)); i++)
		{
			// if space or NULL found, assign NULL into newString[ctr]
			if (stringInFile[i] == ' ' || stringInFile[i] == '\0' || stringInFile[i] == '\n' || stringInFile[i] == ',' || stringInFile[i] == '.' || stringInFile[i] == ';' || stringInFile[i] == ':')
			{
				word[stringIndex] = '\0';

				int wordIndex = findIndexByNameForWords(word, words, allWordsCounter);
				if (wordIndex == -1) {
					strcpy(words[allWordsCounter].name, word);
					words[allWordsCounter].size = strlen(word);
					words[allWordsCounter].count = 1;
					words[allWordsCounter].isChanged = false;
					words[allWordsCounter].value = strlen(word);
					allWordsCounter++;
				}
				else {
					words[wordIndex].count = words[wordIndex].count + 1;
					words[wordIndex].value = words[wordIndex].value + strlen(word);
				}
				stringIndex = 0;    //for next word, init index to 0
			}
			else
			{
				word[stringIndex] = stringInFile[i];
				stringIndex++;
			}
		}
	}
	/*for (int i = 0; i < allWordsCounter; i++) {
		printf("name: %s -> size: %d count: %d\n", words[i].name, words[i].size, words[i].count);
	}*/
	qsort(words, allWordsCounter, sizeof(words[0]), compare);
	int oldValueCount = 0;
	printf("Sorted\n");
	for (int i = 0; i < allWordsCounter; i++) {
		oldValueCount = oldValueCount + words[i].value;
		printf("name: %s -> size: %d count: %d totalSize: %d\n", words[i].name, words[i].size, words[i].count, words[i].value);
	}
	printf("Total value before compose: %d\n", oldValueCount);

	int dictionaryCounter = 0;
	for (int i = 0; i < allWordsCounter; i++) {
		if (words[i].isChanged) continue;
		
		for (int j = 1; j < allWordsCounter; j++) {
			if (words[j].isChanged) continue;

			if (words[i].size != 0 && words[i].count > 1 && (words[i].value + words[j].value) >((words[i].size * words[j].count) + (words[j].size * words[i].count))) {
				strcpy(words[i].changeTo, words[j].name);
				strcpy(words[j].changeTo, words[i].name);
				
				strcpy(dictionary[dictionaryCounter].sourceName, words[i].name);
				strcpy(dictionary[dictionaryCounter].destinationName, words[j].name);


				dictionaryCounter++;
			
				words[i].value = strlen(words[j].name) * words[i].count;
				words[j].value = strlen(words[i].name) * words[j].count;
				words[i].isChanged = true;
				words[j].isChanged = true;
				break;
			}
		}
	}
	int valueCount = 0;
	printf("Changed\n");
	for (int i = 0; i < allWordsCounter; i++) {
		valueCount = valueCount + words[i].value;
			printf("name: %s -> count:%d  new value: %d changeTo: %s\n", words[i].name, words[i].count, words[i].value, words[i].changeTo);
	}
	printf("Total value after compose: %d\n", valueCount);


	for (int i = 0; i < dictionaryCounter; i++) {
		printf("Word: %s\t", words[i].name);
		fprintf(dictionaryFile, "source %s->destination %s \n", dictionary[i].sourceName, dictionary[i].destinationName);
	}

	fclose(file);	
	file = fopen("file.txt", "r+");

	compressFile(file, dictionary, dictionaryCounter);
	fclose(file);

	fclose(dictionaryFile);

}