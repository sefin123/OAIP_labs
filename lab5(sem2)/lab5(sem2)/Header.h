#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_STRING_LENGTH 256
#define HASH_SIZE 5

typedef struct Hash {
	char key[MAX_STRING_LENGTH];
	char value[MAX_STRING_LENGTH];
	struct Hash* prev;
	struct Hash* next;
}Hash;

typedef struct Queue {
	struct Hash* head;
	struct Hash* tail;
}Queue;

typedef struct HashTable {
	int size;
	struct Queue** table;
}HashTable;

int checkIPWithValidation(char* ip);

unsigned int convertHash(const char* str);

void addDomainToFile(char* search);

void push(HashTable* hash, char* domain, char* ip);

void CNAMECheck(char* newDomain);

void findInFile(HashTable* hash, char* search);

void findIPByDomain(HashTable* hash, char* search);

void printTable(HashTable* hash);

void findDomainByIP();

void freeNode(Hash* node);

void freeHashTable(HashTable* hash);