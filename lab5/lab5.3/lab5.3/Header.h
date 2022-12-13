#pragma once
int enterWithValidation();
int enterMatrixWithValidation();
int** allocateMemoryForArray(int row, int col);
int** fillMatrix(int** matrix, int row, int col);
void printArr(int** matrix, int row, int col);
void search(int** matrix, int row, int col, int number);
void deleteElement(int** matrix, int col, int rowIndex, int columnIndex);
void freeMatrix(int* matrix, int row);