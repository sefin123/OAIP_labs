#pragma once

int enterWithValidation();
int enterWithValidationForIndex(int index);
char* enterString();
int stringLength(const char* str);
struct library;
void enterBook(int size, struct library* book);
void printBook(int size, struct library* book);
void sortBooksName(struct library* book, int size);
void sortBooksPages(struct library* book, int size);
void sortBooksYear(struct library* book, int size);
void changingParameters(int size, struct library* book, int valueMenu);
void sortBooks(struct library* book, int size);
void menu(int size, struct library* book);