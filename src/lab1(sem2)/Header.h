#pragma once

int enterWithValidation();

int enterWithValidationForIndex(int index);

char* enterString();

int stringLength(const char* str);

enum Color {
	Red = 1,
	Blue,
	Black,
};

struct library {
	char* name;
	int year;
	int pages;
	enum Color color;
};

char* colorToString(enum Color color);

void enterBook(int size, struct library* book);

void printBook(int size, struct library* book);

void sortBooksName(struct library* book, int size);

void sortBooksPages(struct library* book, int size);

void sortBooksYear(struct library* book, int size);

void deleteBook(struct library* book, int* size, int valueDelete);

void changingParameters(int size, struct library* book, int valueMenu);

void sortBooks(struct library* book, int size);

void menu(int size, struct library* book);