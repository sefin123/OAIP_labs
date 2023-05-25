#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Header.h"

int main() {

	printf("enter amount book: ");
	int size = enterWithValidation();
	
	struct library *book = calloc(size,sizeof(book));

	menu(size, book);

	return 0;
}