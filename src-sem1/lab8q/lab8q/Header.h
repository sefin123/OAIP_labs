#pragma once

#include<stdio.h>
#include<stdlib.h>

void memory(char** string1, int argc, char** argv);

void copy(char** string1, int argc, char** argv);

void swap(char** left, char** right);

int entering(char* string);

void* longest_words(char** str, int* length, int n, int* max);

void merge(int* mas_i, int* mas, int left, int right);

void* merge_sort(int* mas_i, int* mas, int l, int r);

int len_string(char* string);

int min_len_word(char* string, int len_of_string);

void quick_sort(char** string, int first, int last);

void output(char** string, int argc);

void free_memory(char** string, int argc);

void check(int argc);