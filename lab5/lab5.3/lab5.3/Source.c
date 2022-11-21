#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int checkEnter(int variable) {
    while (scanf_s("%d", &variable) != 1 || getchar() != '\n' || variable < 1) {
        printf("Pls enter a number!\n");
        rewind(stdin);
    }
    return variable;
}

int checkEnterArr(int variable) {
    while (scanf_s("%d", &variable) != 1 || getchar() != '\n') {
        printf("Pls enter a number!\n");
        rewind(stdin);
    }
    return variable;
}

int* fillArrFirst(int row, int col) {
    int* arrFirst = malloc(row * sizeof(int));
    for (int i = 0; i < row; i++) arrFirst[i] = col;
    return arrFirst;
}

int** fillArrSecond(int row, int col) {
    int** arrSecond = calloc(row, sizeof(int*));
    for (int i = 0; i < row; i++) {
        arrSecond[i] = calloc(col, sizeof(int));
        for (int j = 0; j < col - 1; j++) {
            arrSecond[i][j] = checkEnterArr(arrSecond[i][j]);
        }
    }
    return arrSecond;
}

void printArr(int** arrSecond, int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%3d", arrSecond[i][j]);
        }
        printf("\n");
    }

}

void deleteElement(int** a, int m, int rowIndex, int columnIndex)
{
    for (int i = columnIndex; i < m - 1; i++) {
        int b = a[rowIndex][i];
        a[rowIndex][i] = a[rowIndex][i + 1];
        a[rowIndex][i + 1] = b;
    }
}

void search(int** a, int n, int* mstring, int k) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < mstring[i]; j += 2) {
            if (a[i][j] < k) {
                deleteElement(a, mstring[i], i, j);
                mstring[i]--;
                j--;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < mstring[i]; j++) {
            printf("%5d ", a[i][j]);
        }
        printf("\n");
    }
}