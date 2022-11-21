#pragma once
int checkEnter(int variable);
int checkEnterArr(int variable);
int* fillArrFirst(int row, int col);
int** fillArrSecond(int row, int col);
void printArr(int** arrSecond, int row, int col);
void search(int** arrSecond, int row, int* arrFirst, int number);
void deleteElement(int** a, int m, int rowIndex, int columnIndex);