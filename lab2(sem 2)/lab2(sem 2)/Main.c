#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Header.h"


int findIndexByName(char* name, Word* words, int size) {
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


int main() {
	Word words[256];
	char stringInFile[256];
	FILE* file = fopen("file.txt", "r");;
	
	char allWords[256][256];
	int allWordsCounter = 0;
	int stringIndex = 0;
	while ((fgets(stringInFile, 256, file)) != NULL)
	{
		char word[256];
		for (int i = 0; i <= (strlen(stringInFile)); i++)
		{
			// if space or NULL found, assign NULL into newString[ctr]
			if (stringInFile[i] == ' ' || stringInFile[i] == '\0' || stringInFile[i] == '\n')
			{
				word[stringIndex] = '\0';

				int wordIndex = findIndexByName(word, words, allWordsCounter);
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


	for (int i = 0; i < allWordsCounter; i++) {
		if (words[i].isChanged) continue;
		
		for (int j = 1; j < allWordsCounter; j++) {
			if (words[j].isChanged) continue;

			if (words[i].size != 0 && words[i].count > 1 && (words[i].value + words[j].value) >((words[i].size * words[j].count) + (words[j].size * words[i].count))) {
				strcpy(words[i].changeTo, words[j].name);
				strcpy(words[j].changeTo, words[i].name);

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

	fclose(file);


	// Получить готовый массив структур check
	// Отсортировать массив структур check
	// Вызвавать decode пока размер меняется


}