#include "Header.h"
#include <stdio.h>
#include <malloc.h>

int enterWithValidation() {
    int a;
    while (scanf_s("%d", &a) != 1 || a < 1 || a % 1 != 0 || getchar() != '\n') {
        printf("error\n");
        rewind(stdin);
    }
    return a;
}

int** fillMatrix(int row, int col) {
    int** matrix =(int**) calloc(row, sizeof(int*));
    for (int i = 0; i < row; i++) {
        matrix[i] =(int*) calloc(col, sizeof(int));
        for (int j = 0; j < col; j++) {
            matrix[i][j] = enterWithValidation(matrix);
        }
    }
    return matrix;
}

void printMatrix(int** matrix, int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void checkElement(int** matrix, int row, int col) {
    for (int i = 0; i < row; i++) {
         int sum = 0;
             for (int j = 0; j < col; j++) {
                 sum = sum + matrix[i][j];
             }
             for (int j = 0; j < col; j++) {
                 if (matrix[i][j] > sum - matrix[i][j]) {
                     printf("%d row have the element at position %d\n" , i, j);
                     break;
                 }
                 else printf("%d row have not the element\n", i);
                 break;
             }
    }
}