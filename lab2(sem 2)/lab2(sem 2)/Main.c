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
			words[i].count = words[i].count + 1;
			return i;
		}
	}
	return -1;
}

int compare(const void* a, const void* b)
{
	
	word* wordsA = (word*)a;
	word* wordsB = (word*)b;
	return ((wordsB->count) - (wordsA->count * wordsA->count));

}

word** prepareWordsStruct(int *wordsIterator) {
	int memorySize = 0;
	FILE* file = fopen("file.txt", "r");
	word* words = calloc(2 , sizeof(word));

	//if (fopen == NULL) printf("file is open\n");
	//else printf("file isnt open\n");

	char* str = malloc(4096 * sizeof(char));
	while (fgets(str, 4096, file)) {
		int i = 0;
		while (str[i] != '\n') {
			while (!isLetter(str[i])) i++;
		
			int wordSize = getWordSize(str, i);

			char* stringWord = calloc(wordSize + 1 , sizeof(char));
			if (!stringWord) exit(1);
			//qwe wqer qwe qwer qwer

			for (int j = 0, k = i; j < wordSize; k++, j++) {
				stringWord[j] = str[k];
			}

			int existedWordIndex = findIndexWordInWordsStructByName(words, stringWord, *wordsIterator);

			if (existedWordIndex == -1) {
				memorySize = memorySize + wordSize + 4;
			
				//words = realloc(words, memorySize);
				
				if(!words) exit(1);
				
				word newWord;
				newWord.name = strdup(stringWord);

				words[*wordsIterator] = newWord;
				*wordsIterator = *wordsIterator + 1;
			}
			else {
				//words[existedWordIndex].count = words[existedWordIndex].count + 1;
			}
			i = i + wordSize /* (-1???)*/;
		}
	}
	return words; 
}


//


int main() {
	int wordsIterator = 1;

	word* words = prepareWordsStruct(&wordsIterator);

	for (int i = 0; i<wordsIterator; i++) {
		printf("name: %s ", words[i].name);
		printf("count %d\n", words[i].count);
	}

	qsort(words, wordsIterator, sizeof(words[0]), compare);
	
	for(int i = 0; i< wordsIterator; i++) {
		printf("name: %s ", words[i].name);
		printf("count %d\n", words[i].count);
	}	
	return 0;
}