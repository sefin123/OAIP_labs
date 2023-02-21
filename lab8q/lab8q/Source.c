#include "Header.h"

void memory(char** string, int argc, char** argv) {
	for (int i = 1; i < argc; i++) {
		int strLen = len_string(argv[i]);
		string[i - 1] = (char*)calloc(strLen + 1, sizeof(char));
		string[i - 1][strLen] = '\0';
	}
}

void copy(char** string, int argc, char** argv) {
	for (int i = 1; i < argc; i++) {
		int str_len = len_string(argv[i]);
		for (int c = 0; c < str_len; c++)
			string[i - 1][c] = argv[i][c];
	}
}

void* merge_sort(int* max) {

}

void* merge_sortt(int* mas_i, int* mas, int l, int r) {
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

int len_string(char* string) {
	int temp = 0;
	while (string[temp] != '\0') {
		temp++;
	}
	return temp;
}

void output(char** string, int argc) {
	for (int i = 0; i < argc; i++) {
		printf("\t%s\n", string[i]);
	}
}

void free_memory(char** string, int argc) {
	for (int i = 0; i < argc; i++) {
		free(string[i]);
	}
	free(string);
}

void check(int argc) {
	if (argc == 1) printf("\nYou havent rows to sort\n");
	return;
}