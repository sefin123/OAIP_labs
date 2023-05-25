#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

int enterWithValidationForIndex(int value);

int checkIPWithValidation(char* ip);

List* mapBucket(HashTable* self, const char* key);

Node* findNode(HashTable* self, const char* key);

unsigned int convertHash(const char* str);

void setInHash(HashTable* self, char* key, char* value);

char* findIpInFile(char* search);

void findIP(char* domain, FILE* source, HashTable* cache);

char* findCNAMEDomain(char* newDomain);

void printCache(HashTable* lru);

void findDomainByIP();

HashTable* initHashTable(HashTable* self);

void printTable(HashTable* hash);

void freeHash(HashTable* hash);