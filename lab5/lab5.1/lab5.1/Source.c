#include "Header.h"
#include <stdio.h>
#include <malloc.h>

int checkEnter(int a) {
    while (scanf_s("%d", &a) != 1 || getchar() != '\n') {
        printf("error\n");
        rewind(stdin);
    }
    return a;
}

void checkElement(int** arrSecond, int row, int col) {
    for (int i = 0; i < row; i++) {
         int sum = 0;
             for (int j = 0; j < col; j++) {
                 sum = sum + arrSecond[i][j];
             }
             for (int j = 0; j < col; j++) {
                 if (arrSecond[i][j] > sum - arrSecond[i][j]) {
                     printf("%d row have the element\n" , i);
                     break;
                 }
                 else printf("%d row have not the element\n", i);
                 break;
             }
    }
}