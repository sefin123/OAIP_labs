#pragma once
#include <stdbool.h>

typedef struct Word {
	char changeTo[50];
	char name[50];
	int size;
	int count;
	int value;
	bool isChanged;
} Word;
