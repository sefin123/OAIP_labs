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

Node* deserializeTree(FILE* in);

void gameAkinator(Node* root);

void serializeTree(Node* root, FILE* out);

void freeTree(Node* node);