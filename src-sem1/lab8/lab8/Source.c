#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

void* checkEnter() {
    int a;
    while (scanf_s("%d", &a) != 1 || getchar() != '\n') {
        printf("Pls enter a NUMBER\n");
        rewind(stdin);
    }
    return a;
}

void* str_len(char* str, int* len) {
    int i = 0;
    while (str[i] != '\0') {
        i++;
        (*len)++;
    }
    return str_len;
}

void* enterString(char** string)
{
    int char_;
    int i = 0;
    rewind(stdin);
    while ((char_ = getchar()) != EOF && char_ != '\n')
    {
        (*string)[i++] = char_;
        (*string) = (char*)realloc((*string), (i + 1) * sizeof(char));
    }
    (*string)[i] = '\0';
    return enterString;
}


void* merge_sort(int* mas_i, int* mas, int l, int r) {
    int p1 = 0, p2 = 0, mid = (l + r) / 2, pos = 0;
    int* b = NULL;
    int* b_i = NULL;
    b_i = (int*)calloc((r + 1), sizeof(int));
    b = (int*)malloc((r + 1) * sizeof(int));
    int i = 0;
    while (p1 + l <= mid && mid + p2 + 1 <= r) {
        if (p1 > mid || mid + 1 + p2 > r) break;

        if (mas[p1 + l] < mas[mid + 1 + p2]) {
            b[i] = mas[p1 + l];
            b_i[i] = mas_i[p1 + l];
            i++;
            p1++;
        }
        else {
            b[i] = mas[mid + 1 + p2];
            b_i[i] = mas_i[mid + 1 + p2];
            i++;
            p2++;
        }

    }
    while (p1 + l <= mid) {
        b[i] = mas[p1 + l];
        b_i[i] = mas_i[p1 + l];
        i++;
        p1++;
    }
    while (mid + 1 + p2 <= r) {
        b[i] = mas[mid + 1 + p2];
        b_i[i] = mas_i[mid + 1 + p2];
        i++;
        p2++;
    }
    pos = 0;
    for (int i = l; i <= r; i++) {
        mas[i] = b[pos];
        mas_i[i] = b_i[pos];
        pos++;
    }
    free(b);
    return merge_sort;
}

void merge(int* mas_i, int* mas, int left, int right) {
    if (left == right)return;
    int mid = (left + right) / 2;
    merge(mas_i, mas, left, mid);
    merge(mas_i, mas, mid + 1, right);
    merge_sort(mas_i, mas, left, right);
}



void* longest_words(char** str, int* length, int n, int* max) {
    for (int i = 0; i < n; i++) {
        int k = 0;
        max[i] = 999;
        for (int j = 0; j < length[i]; j++) {
            k++;
            if (str[i][j + 1] == ' ' || str[i][j + 1] == '\0' || str[i][j + 1] == '\n') {
                if (max[i] > k) {
                    max[i] -= k;
                }
                k = -1;
            }
        }
    }
    return longest_words;
}

/*void foundShortestWord(char** str, int len) {

    int minWord = 9999999;
    int curentyWord = 1;
    int indexWords = 0;
    int indexShortestWord = 0;
    
    for (int i = 0; i <= len; i++) {
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
    return foundShortestWord;
}*/

void copy(char** string, int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        int str_len = len_string(argv[i]);
        for (int c = 0; c < str_len; c++)
            string[i - 1][c] = argv[i][c];
    }
}

int len_string(char* string) {
    int temp = 0;
    while (string[temp] != '\0') {
        temp++;
    }
    return temp;
}

void memory(char** string, int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        int strLen = len_string(argv[i]);
        string[i - 1] = (char*)calloc(strLen + 1, sizeof(char));
        string[i - 1][strLen] = '\0';
    }
}

int main(int argc, char** argv) {
    int* len;
    int* max;
    int* max_ind;
    char** str;
    
    str = (char**)calloc(argc, 1 * sizeof(char*));
    max = (int*)calloc(argc, sizeof(int));
    max_ind = (int*)calloc(argc, sizeof(int));
    len = (int*)malloc(argc * sizeof(int));
    
    memory(str, argc, argv);
    copy(str, argc, argv);

    for (int i = 0; i < argc; i++) {
        max_ind[i] = i;
        len[i] = 0;
        str_len(str[i], &len[i]);
    }

    longest_words(str, len, argc, max);
    merge(max_ind, max, 0, argc - 1);

    for (int i = 0; i < argc; i++)
        printf("%s\n", str[max_ind][i]]);
    for (int i = 0; i < argc; i++) {
        free(str[i]);
    }
    free(str);
    free(max);
    free(max_ind);
    free(len);
    return 0;
}