#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 256
#define NULL_STRING "NULL"

void freeTree(Node** node);

Node* createNode(const char* word, Node* left, Node* right);

Node* deserializeTree(FILE* in);

void serializeTree(Node* root, FILE* out);


