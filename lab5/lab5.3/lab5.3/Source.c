#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#define INFINITY = -1000000000;


int checkEnter(int variable) {
    while (scanf_s("%d", &variable) != 1 || getchar() != '\n' || variable < 1) {
        printf("Pls enter a number!\n");
        rewind(stdin);
    }
    return variable;
}

int checkEnterArr() {
    int variable;
    while (scanf_s("%d", &variable) != 1 || getchar() != '\n') {
        printf("Pls enter a number!\n");
        rewind(stdin);
    }
    return variable;
}

int** allocateMemoryForArray(int row, int col) {
    int** matrix = (int**)calloc(row, sizeof(int*));
    for (int i = 0; i < row; i++) {
        matrix[i] = (int*)calloc(col, sizeof(int));

    }
    return matrix;

}

int** fillMatrix(int** matrix, int row,int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col - 1; j++) {
            matrix[i][j] = checkEnterArr();
        }
    }
    return matrix;
}

void printArr(int** arrSecond, int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%3d", arrSecond[i][j]);
        }
        printf("\n");
    }

}

void deleteElement(int** a, int col, int rowIndex, int columnIndex) {
    for (int i = columnIndex; i < col - 1; i++) {
        int b = a[rowIndex][i];
        a[rowIndex][i] = a[rowIndex][i + 1];
        a[rowIndex][i + 1] = b;
    }
}


void prettyPrintArray(int** matrix, int row, int col, int* howMuchBeloveValue) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col - howMuchBeloveValue[i]; j++) {
            printf("%3d", matrix[i][j]);
        }
        printf("\n");
    }
}

//void search(int** matrix, int row, int col, int number) {
//    int* howMuchElementBeloveValueOnRow = calloc(row, sizeof(int));
//
//    for (int i = 0; i < row; i++) {
//        int count = 0;
//        for (int j = 0; j < col - 1 ; j += 2) {
//            if (matrix[i][j] < number) {
//                deleteElement(matrix, col, i, j);
//                count++;
//            }
//        }
//        howMuchElementBeloveValueOnRow[i] = count;
//        matrix[i] = realloc(matrix[i], (col - count) * 4);
//    }
//    prettyPrintArray(matrix, row, col, howMuchElementBeloveValueOnRow);
//}

void search(int** matrix, int row, int col, int number) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j ++) {
            if (j % 2 == 0 && matrix[i][j] < number) {
                matrix[i][j] = -100;
            }
            else
                printf("%3d", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < row; i++) {
        int count = 0;
        for (int j = 0; j < col; j ++) {
            if (matrix[i][j] == -100) {
                count++;
                deleteElement(matrix, col, i, j);
            }
            
        }
        matrix[i] = realloc(matrix[i], (col - count) * 4);
    }
}