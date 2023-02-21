#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

char* append(char* str, size_t len, int ch) {
    char* new = realloc(str, (len + 2) * sizeof(*str));
    if (new == NULL) assert(!"NULL ptr after realloc!");

    new[len] = ch;
    new[len + 1] = 0;
    return new;
}

char* enterPrintString() {

    char* str = calloc(1, sizeof(*str));
    size_t len = 0;
    int ch;
    bool flag = false;
    while (!flag) {
        str = calloc(1, sizeof(*str));
        size_t len = 0;
        flag = true;
        while ((ch = getchar()) != '\n') {
            str = append(str, len++, ch);
            if ((ch > 64 && ch < 91) || (ch > 96 && ch < 123) || ch == 32 || ch == '\t') {

            }
            else {
                flag = false;
            }

        }
    }
    printf("%s\n", str);
    return str;
}

void foundShortestWord(char* str, int len) {

    int minWord = 9999999;
    int curentyWord = 1;
    int indexWords = 0;
    int indexShortestWord = 0;
    for (int i = 0; i <= len; i++) {
        if (i == len) {
            printf("%c", str[i]);
        }
        if (str[i] == ' ' || str[i] == '\0' || str[i] == '\t') {
            indexWords++;
            if (curentyWord < minWord) {
                minWord = curentyWord;
                indexShortestWord = indexWords;
            }
            curentyWord = 0;
        }
        else {
            curentyWord++;
        }
    }
    printf("%d", indexShortestWord);

}

void newString(char* strFirst, int lenFirst, char* strSecond, int lenSecond, int k) {

    char* result = calloc(lenFirst + k, sizeof(char));
    int indexResult = 0;

    for (int i = 0; i < lenFirst / 2; i++) {
        result[indexResult] = strFirst[i];
        indexResult++;
    }

    for (int i = lenSecond - k; i < lenSecond; i++) {
        result[indexResult] = strSecond[i];
        indexResult++;
    }

    for (int i = (lenFirst / 2); i < lenFirst; i++) {
        result[indexResult] = strFirst[i];
        indexResult++;
    }

    result[indexResult] = '\0';

    printf("%s", result);

}

int enterWithValidation1(int lenSecond) {
    int a;

    while (scanf_s("%d", &a) != 1 || a > lenSecond || getchar() != '\n') {
        printf("Error\n");
        rewind(stdin);
    }

    return a;
}

int enterWithValidation(int lenSecond) {
    int a;

    while (scanf_s("%d", &a) != 1 || a < 1 || getchar() != '\n') {
        printf("Error\n");
        rewind(stdin);
    }

    return a;
}

void taskFirst() {
    char* str = enterPrintString();

    int len = strlen(str);

    foundShortestWord(str, len);

    free(str);

}

void taskSecond() {

    char* strFirst = enterPrintString();

    int lenFirst = strlen(strFirst);

    char* strSecond = enterPrintString();

    int lenSecond = strlen(strSecond);

    int k = enterWithValidation1(lenSecond);

    newString(strFirst, lenFirst, strSecond, lenSecond, k);

    free(strFirst);
    free(strSecond);

}