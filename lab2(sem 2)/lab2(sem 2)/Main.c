#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Header.h"


bool isLetter(char letter) {
	return letter != ' ' && letter != '\n';
}

int getWordSize(char* string, int startIndex) {
	int wordSize = 0;
	for (int i = startIndex; isLetter(string[i]); i++) {
		wordSize++;
	}
	return wordSize;
}

int findIndexWordInWordsStructByName(word* words, char* name, int wordCount) {
	for (int i = 0; i < wordCount; i++)
	{
		if (!strcmp(words[i].name, name)) {
			return i;
		}
	}
	return -1;
}


word** prepareWordsStruct() {
	FILE* file = fopen("file.txt", "r");
	word* words = calloc(1, sizeof(word));
	int wordsIterator = 0;

	if (fopen == NULL) printf("file is open\n");
	else printf("file isnt open\n");

	char* str = calloc(256, sizeof(char));
	while (fgets(str, 256, file)) {
		int i = 0;
		while (str[i] != '\n') {
			while (!isLetter(str[i])) i++;
		
			int wordSize = getWordSize(str, i);

			char* stringWord = calloc(wordSize, sizeof(char));

			for (int j = 0, k = i; k < wordSize - 1, j < wordSize - 1; k++, j++) {
				stringWord[j] = str[k];
			}

			int existedWordIndex = findIndexWordInWordsStructByName(words, stringWord, wordsIterator);

			if (existedWordIndex == -1) {
				realloc(words, (wordsIterator + 1) * sizeof(word));
				word newWord = { .isEmpty = false, .name = stringWord, .size = wordSize, .count = 0 };
				words[wordsIterator] = newWord;
				wordsIterator++;
			}
			else {
				words[existedWordIndex].count = words[existedWordIndex].count + 1;
			}
			i = i + wordSize;
		}
	}
	return words; 
}


int main() {
	word* words = prepareWordsStruct();
	int i = 0;
	while (!words[i].isEmpty) {
		printf("name: %s", words[i].name);
		printf("size: %d", words[i].size);
		printf("count %d\n", words[i].count);
			i++;
	}	
	return 0;
}