#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STRING_LENGTH 256
#define HASH_SIZE 5

typedef struct HashTable HashTable;

typedef struct Data Data;

struct Data {
    char key[MAX_STRING_LENGTH];
    char value[MAX_STRING_LENGTH];
};

typedef struct Node Node;

struct Node{
    Data data;
    Node *next;
    Node *prev;
};

typedef struct List List;

struct List {
    Node *head;
    Node *tail;
};

struct HashTable {
    List buckets[HASH_SIZE];
    Node* head;
    Node* tail;
    int count;
};

bool empty(List *self);

void pushFront(List* self, Data data);

void pushNodeFront(List *self, Node *new);

void pushNode(List *self, Node *new);

List *initList(List *self);

void insertNodeAfter(Node *that, Node *new);

void insertNodeBefore(Node* that, Node* new);

void freeNode(Node *what);

void detachFromList(List *self, Node *what);

Node *initNode(Node *self, Data data);