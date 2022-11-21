#pragma once
#include <stdbool.h>

int** allocateMemoryForArray(int size);
int** fillMatrix(int** matrix, int size);
void printMatrix(int** matrix, int size);
bool isSymmetric(int** arr, int size);
void newArr(int** arr, int size, bool sim);
int enterWithValidation(int a);