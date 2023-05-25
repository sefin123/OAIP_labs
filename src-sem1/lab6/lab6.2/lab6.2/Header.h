#include <stdbool.h>
#pragma once
int enterWithValidation();
int** allocateMemoryForArray(int row, int col);
int** fillMatrix(int** matrix, int row, int col);
void printMatrix(int** matrix, int row, int col);
bool lessThen(const int* left, const int* right, int size);
void quickSort(int** matrix, int left, int right, int width);
int sum(const int* arr, int size);
void swap(int** a, int** b);