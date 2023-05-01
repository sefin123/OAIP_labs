#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 256
#define NULL_STRING "NULL"

typedef struct Node {
    char word[MAX_STRING_LENGTH];
    struct Node* left;
    struct Node* right;
} Node;

int enterWithValidation();

void correctAnswersTree(Node* node);

void gameAkinator(Node* root);
