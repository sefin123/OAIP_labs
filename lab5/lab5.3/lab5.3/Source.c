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

void deleteElement(int** arrFirst, int col, int rowIndex, int columnIndex)
{
    for (int i = columnIndex; i < col - 1; i++) {
        int b = arrFirst[rowIndex][i];
        arrFirst[rowIndex][i] = arrFirst[rowIndex][i + 1];
        arrFirst[rowIndex][i + 1] = b;
    }
}

void search(int** arrSecond, int row, int* arrFirst, int number) {
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < arrFirst[i]; j += 2)
        {
            if (arrSecond[i][j] < number)
            {
                deleteElement(arrSecond, arrFirst[i], i, j);
                arrFirst[i]--;
                j--;
            }
        }
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < arrFirst[i]; j++)
        {
            printf("%5d ", arrSecond[i][j]);
        }
        printf("\n");
    }
}