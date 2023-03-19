#include <stdio.h>
#include <stdlib.h>
#include "Header.h"


word** prepareWordsStruct() {
	// прочесть файл
	FILE* file = fopen("file.txt", "r");
	if (fopen == NULL) printf("file is open\n");
	else printf("file isnt open\n");
	char* str = calloc(256, sizeof(char));
	while (fgets(str, 256, file)) {

	}

	// заполнить массив структур
	struct word* words = calloc(1, sizeof(word));
	// вернить массив структур
	return words ;
}


int isMeet(word* word,char* buf) {
	int i = 0;
	while (i != NULL) {
		if (buf == word[i].word) {
			word[i].count++;
			return 1;
		}
		i++;
	}
	return 0;
}

void searchWord(char* str,word* words) {
	int i = 0;
	int wordsIterator = 0;
	while (str[i] != '\n') {
		while (str[i] == ' ' || str[i] == '\t' || str[i] == ',' || str[i] == '.' || str[i] == ':' || str[i] == ';') i++;
		if (str[i] >= 'A' || str[i] <= "Z" || str[i] >= 'a' || str[i] <= 'z') {
			int sizeOfWord = 0;
			while (str[i] != ' ' && str[i] != '\t' && str[i] != ',' && str[i] != '.' && str[i] != ':' && str[i] != ';') sizeOfWord++;
			words[wordsIterator].size = sizeOfWord;
			char* buf = calloc(sizeOfWord, sizeof(char));
			for (int j =  0,k = i; k < sizeOfWord, j < sizeOfWord; k++, j++) {
				buf[j] = str[k];
				if (isMeet(words, buf)) break;
				words[wordsIterator].name = str[k];
			}
		}
		i++;
	}
}

int main() {

	/*struct word *words = calloc(1, sizeof(word));

	FILE* file;
	int res = fopen_s(&file, "file.txt", "r+");
	if (res == NULL) printf("file is open\n");
	else printf("file isnt open\n");
	char *str = calloc(256,sizeof(char));
	while (fgets(str, 256, file)) {
		printf(str);
		searchWord(str,words);
	}
	printf("\n");
	fclose(file);
	if ((fclose(file)) != NULL) printf("file is close");
	else printf("file isnt close");*/


	return 0;
}