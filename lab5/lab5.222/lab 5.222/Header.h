#pragma once
#include <stdbool.h>

int** fillMatrix(int size);
void printMatrix(int** matrix, int size);
bool isSymmetric(int** arr, int size);
void newArr(int** arr, int size, bool sim);
int enterWithValidation(int a);