#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>
int* mergeArr(int* arrF, int* arrS,int sizeF,int sizeS) {
    arrF = realloc(arrF, (sizeS + sizeF) * sizeof(int));
    int j = 0;
    for (int i = sizeF; i < sizeS+sizeF; i++) {
        arrF[i] = arrS[j];
        j++;
    }
    return arrF;
}
void swap(int* arr,int i, int j) {
    int t = arr[i];
    arr[i] = arr[j];
    arr[j] = t;
}
void quickSort(int* arr, int l, int r) {
    int i = l, j = r, pivot = arr[(i + j) / 2];
    do {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            swap(arr, i, j);
            i++;
            j--;
        }
    } while (i <= j);
        if (j > l) quickSort(arr, l, j);
        if (i < r) quickSort(arr, i, r);
}
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int* L = calloc(n1, sizeof(int));
    int* R = calloc(n2, sizeof(int));
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(int arr[], int l, int r)
{
    if (l < r) {
        int m = (r + l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}
void shellSort(int size, int* arr)
{
    int i, j, step;
    int tmp;
    for (step = size / 2; step > 0; step /= 2) {
        for (i = step; i < size; i++) {
            tmp = arr[i];
            for (j = i; j >= step; j -= step) {
                if (tmp < arr[j - step])
                    arr[j] = arr[j - step];
                else
                    break;
            }
            arr[j] = tmp;
        }
    }
}
void viborSort(int* arr, int size) {
    int minPosition, tmp;
    for (int i = 0; i < size; i++)
    {
        minPosition = i;
        for (int j = i + 1; j < size; j++)
            if (arr[minPosition] > arr[j])
                minPosition = j;
        tmp = arr[minPosition];
        arr[minPosition] = arr[i];
        arr[i] = tmp;
    }
}
void vstavkaSort(int size, int* arr)
{
    int newElement, location;

    for (int i = 1; i < size; i++)
    {
        newElement = arr[i];
        location = i - 1;
        while (location >= 0 && arr[location] > newElement)
        {
            arr[location + 1] = arr[location];
            location = location - 1;
        }
        arr[location + 1] = newElement;
    }
}
void bubbleSort(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {

        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

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
void delWord(char* str, int len,int k) {
    int i = 0;
    int word = 0;
    int wordSize = 0;
    while (str[i] != '\0') {
        while (str[i] == ' ') i++;
        word++;
        if (word == k) {
            while (str[i] != ' ' && str[i] != '\0') {
                i++;
                wordSize++;
            }
            break;
        }
        else {
            while (str[i] != ' ' && str[i] != '\0') i++;
        }
    }
    for (i -= wordSize; i < len - wordSize + 1; i++)
        str[i] = str[i + wordSize];
    str = realloc(str, (len - wordSize + 1) * sizeof(char));
}

int main() {
    int k = 0;
    char* str = enterPrintString();
    printf("enter k\n");
    scanf_s("%d", &k);
    int i = 0;
    int len = 0;
    while (str[i] != '\0') {
        len++;
        i++;
    }
    delWord(str,len, k); 
    printf("%s", str);
    free(str);


    /*int sizeF = 0;
    int sizeS = 0;
    printf("enter first size\n");
    scanf_s("%d", &sizeF);
    printf("enter second size\n");
    scanf_s("%d", &sizeS);
    int* arrF = calloc(sizeF, sizeof(int));
    int* arrS = calloc(sizeS, sizeof(int));
    for (int i = 0; i < sizeF; i++) {
        scanf_s("%d", &arrF[i]);
    }
    for (int i = 0; i < sizeS; i++) {
        scanf_s("%d", &arrS[i]);
    }
    for (int i = 0; i < sizeF; i++) {
        printf("%3d", arrF[i]);
    }
    printf("\n");
    for (int i = 0; i < sizeS; i++) {
        printf("%3d", arrS[i]);
    }
    printf("\n");
    int size = sizeF + sizeS;
    arrF = mergeArr(arrF, arrS, sizeF, sizeS);
    for (int i = 0; i < sizeF + sizeS; i++) {
        printf("%3d", arrF[i]);
    }
    printf("\n");

    //mergeSort(arrF,0,size - 1,size);
    // quickSort(arrF, 0, size - 1);
    //shellSort(size, arrF);
    //viborSort(arrF, size);
    //vstavkaSort(size, arrF);
    bubbleSort(arrF, size);
    for (int i = 0; i < sizeF + sizeS; i++) {
        printf("%3d", arrF[i]);
    }
    printf("\n");
    */


    return 0;
}