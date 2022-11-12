#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int checkEnter(int a) {
    while (scanf_s("%d", &a) != 1 || getchar() != '\n') {
        printf("error\n");
        rewind(stdin);
    }
    return a;
}

int symmetric(int** arrFirst, int size) {
    bool sim = true;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (arrFirst[i][j] != arrFirst[size - 1 - j][size - 1 - i]) {
                sim = false;
                break;
            }
        }
        if (!sim) {
            break;
        }
    }
    return sim;
}

void newArr(int** arrFirst, int size, bool sim) {
    int** arrSecond = calloc(size, sizeof(*arrSecond));
    if (arrSecond == NULL) abort();
    for (int i = 0; i < size; i++) {
        arrSecond[i] = calloc(size, sizeof(**arrSecond));
        if (arrSecond == NULL) abort();
    }
    if (sim == true) {
        printf("the matrix is symmetric with respect to the secondary diagonal\n");
        for (int i = 0; i < size; i++) {
            int flag = 0;
            for (int j = 0; j < size; j++) {
                if (i == size - j - 1) {
                    flag++;
                    continue;
                }
                arrSecond[i][j - flag] = arrFirst[i][j];
            }
        }
    }
    else {
        printf("the matrix is not symmetric with respect to the secondary diagonal\n");
        for (int i = 0; i < size; i++) {
            int flag = 0;
            for (int j = 0; j < size; j++) {
                if (i == j) {
                    flag++;
                    continue;
                }
                arrSecond[i][j - flag] = arrFirst[i][j];
            }
        }
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            printf("%5d ", arrSecond[i][j]);
        }
        printf("\n");
    }
    free(arrSecond);
}