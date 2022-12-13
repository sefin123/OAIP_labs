#pragma once
int enterWithValidation();
int enterMatrixWithValidation();
int** allocateMemoryForArray(int row, int col);
int** fillMatrix(int** matrix, int row, int col);
void printMatrix(int** matrix, int row, int col);
void checkElement(int** matrix, int row, int col);
void freeMatrix(int* matrix, int row);