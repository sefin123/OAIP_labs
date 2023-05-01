#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_STRING_LENGTH 256

typedef struct Node {
	struct Node* next;
	struct Node* prev;
	char key[MAX_STRING_LENGTH];
	char value[MAX_STRING_LENGTH];
}Node;

typedef struct Data {
	char domain[MAX_STRING_LENGTH];
	char IP[MAX_STRING_LENGTH];
}Data;

typedef struct List {
	Node *head;
	Node *tail;
}List;
