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

int enterWithValidationForIndex(int value) {
	int a;

	while (scanf_s("%d", &a) != 1 || a < 1 || a > value || getchar() != '\n') {
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

void enterBook(int size, struct library* book) {
	for (int i = 0; i < size; i++) {
		printf("\nenter name of %d's book: ", i + 1);
		rewind(stdin);
		book[i].name = enterString();
		printf("\nenter year of %d's book: ", i + 1);
		book[i].year = enterWithValidation();
		printf("\nenter amount pages of %d's book: ", i + 1);
		book[i].pages = enterWithValidation();
		printf("\nenter 1 - 3 for choose the color of %d's book", i + 1);
		printf("\n1.red");
		printf("\n2.blue");
		printf("\n3.black");
		printf("\nchoose: ");
		book[i].color = enterWithValidationForIndex(3);
	}
}

char* colorToString(enum Color color) {
	switch (color) {
	case Red: return "Red";
	case Blue: return "Blue";
	case Black: return "Black";
	}
}

void printBook(int size, struct library* book) {
	for (int i = 0; i < size; i++) {
		printf("\nname of %d's book: %s", i + 1, book[i].name);
		printf("\nyear of %d's book: %d", i + 1, book[i].year);
		printf("\namount pages of %d's book: %d", i + 1, book[i].pages);
		printf("\ncolor of %d's book: %s", i + 1, colorToString(book[i].color));

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

void sortBooksTwoParametrs(struct library* book, int  size) {
	struct library tmp;
	
	for (int i = size - 1; i >= 0; i--) {
		for (int j = 0; j < i; j++) {
            if ((book[j].year > book[j + 1].year) || (book[j].year == book[j + 1].year) && (book[j].pages > book[j + 1].pages)) {
				tmp = book[j];
				book[j] = book[j + 1];
				book[j + 1] = tmp;
			}
		}
	}
}

void deleteBook(struct library* book, int *size,int valueDelete) {
	valueDelete--;
	free(book[valueDelete].name);
	for (int i = valueDelete; i < (*size) - 1; i++) {
		book[i] = book[i + 1];
	}
	(*size)--;
	book = realloc(book, (*size) * sizeof(struct library));
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
	printf("4.sort 2 parametrs\n");
	printf("choice: ");
	int indexSort;
	indexSort = enterWithValidationForIndex(4);
	if (indexSort == 1) sortBooksName(book, size);
	if (indexSort == 2) sortBooksYear(book, size);
	if (indexSort == 3) sortBooksPages(book, size);
	if (indexSort == 4) sortBooksTwoParametrs(book, size);
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
		printf("\n6. delete book");
		printf("\n7. exit\n");
		printf("\nchoice: ");

		int valueMenu;
		valueMenu = enterWithValidationForIndex(7);
		if (valueMenu == 7) exit = false;
		if (valueMenu > 0 && valueMenu < 4 ) changingParameters(size, book, valueMenu);
		if (valueMenu == 4)	sortBooks(book, size);
		if (valueMenu == 5) printBook(size, book);
		if (valueMenu == 6) {
			printf("\nchoose which book to delete\n");
			int valueDelete;
			valueDelete = enterWithValidationForIndex(size);
			deleteBook(book, &size,valueDelete);
		}
			printf("\n");
	}
}