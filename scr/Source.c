#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Header.h"

int enterWithValidation() {
	int a;

	while (scanf_s("%d", &a) != 1 || a < 1 || getchar() != '\n') {
		printf("Error\n");
		rewind(stdin);
	}

	return a;
}

int enterWithValidationForIndex(int index) {
	int a;

	while (scanf_s("%d", &a) != 1 || a < 1 || a > index || getchar() != '\n') {
		printf("Error\n");
		rewind(stdin);
	}

	return a;
}

char* enterString() {
	char* string = calloc(256, sizeof(char));

	gets_s(string, 255);

	int size = stringLength(string);

	string = realloc(string, size + 1);

	return string;
}

int stringLength(const char* str) {
	int length = 0;

	while (str[length] != '\0')
		length++;
	
	return length;
}

struct library {
	char* name;
	int year;
	int pages;
};

void enterBook(int size, struct library* book) {
	for (int i = 0; i < size; i++) {
		printf("\nenter name of %d's book: ", i + 1);
		rewind(stdin);
		book[i].name = enterString();

		printf("\nenter year of %d's book: ", i + 1);
		book[i].year = enterWithValidation();

		printf("\nenter amount pages of %d's book: ", i + 1);
		book[i].pages = enterWithValidation();
	}
}

void printBook(int size, struct library* book) {
	for (int i = 0; i < size; i++) {
		printf("\nname of %d's book: %s", i + 1, book[i].name);
		printf("\nyear of %d's book: %d", i + 1, book[i].year);
		printf("\namount pages of %d's book: %d", i + 1, book[i].pages);
	}
}

void sortBooksName(struct library* book, int size) {
	struct library tmp;

	for (int i = size - 1; i >= 0; i--) {
		for (int j = 0; j < i; j++) {
			if (strcmp(book[j].name, book[j + 1].name) > 0) {
				tmp = book[j];
				book[j] = book[j + 1];
				book[j + 1] = tmp;
			}
		}
	}
}

void sortBooksPages(struct library* book, int size) {
	struct library tmp;

	for (int i = size - 1; i >= 0; i--) {
		for (int j = 0; j < i; j++) {
			if ((book[j].pages) > (book[j + 1].pages)) {
				tmp = book[j];
				book[j] = book[j + 1];
				book[j + 1] = tmp;
			}
		}
	}
}

void sortBooksYear(struct library* book, int size) {
	struct library tmp;

	for (int i = size - 1; i >= 0; i--) {
		for (int j = 0; j < i; j++) {
			if ((book[j].year) > (book[j + 1].year)) {
				tmp = book[j];
				book[j] = book[j + 1];
				book[j + 1] = tmp;
			}
		}
	}
}

void changingParameters(int size, struct library* book,int valueMenu) {
	printf("\nchoose which book to change\n");
	int indexBook;
	indexBook = enterWithValidationForIndex(size);
	if (valueMenu == 1) book[indexBook - 1].name = enterString();
	if (valueMenu == 2) book[indexBook - 1].year = enterWithValidation();
	if (valueMenu == 3) book[indexBook - 1].pages = enterWithValidation();
}

void sortBooks(struct library* book,int size) {
	printf("By what criteria to sort:\n");
	printf("1.Name\n");
	printf("2.Year\n");
	printf("3.Pages\n");
	printf("choice: ");
	int indexSort;
	indexSort = enterWithValidationForIndex(3);
	if (indexSort == 1) sortBooksName(book, size);
	if (indexSort == 2) sortBooksYear(book, size);
	if (indexSort == 3) sortBooksPages(book, size);
}

void menu(int size, struct library* book) {

	enterBook(size, book);
	printf("\n");
	printBook(size, book);
	printf("\n");

	bool exit = true;
	while (exit) {

		printf("\nselect what you wanna do");
		printf("\n1. change the name of the book");
		printf("\n2. change year of the book");
		printf("\n3. change the number of pages of the book");
		printf("\n4. sort books");
		printf("\n5. print books");
		printf("\n6. exit\n");
		printf("\nchoice: ");

		int valueMenu;
		valueMenu = enterWithValidationForIndex(6);
		if (valueMenu == 6) exit = false;
		if (valueMenu > 0 && valueMenu < 4 && exit) changingParameters(size, book, valueMenu);
		if (valueMenu == 4)	sortBooks(book, size);
		if (valueMenu == 5) printBook(size, book);
		printf("\n");
	}
}