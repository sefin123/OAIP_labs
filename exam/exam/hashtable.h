#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY_TABLE 0

#define SIZE_OF_CACHE 5

typedef struct node node;

typedef struct hashtable_object {
	char* key;
	node* node;
} hashtable_object;

typedef struct list {
	hashtable_object* object;
	struct list* next;
} list;

typedef struct hashtable {
	hashtable_object** objects;
	list** chains;
	int size;
	int count;
} hashtable;

typedef struct node {
	char* key;
	char* value;
	struct node* next;
	struct node* prev;
} node;

typedef struct lru_cache {
	hashtable* table;
	node* head;
	node* tail;
	int count;
} lru_cache;

list* create_list();

list* insert_list(list* head, hashtable_object* object);

list* create_chains(hashtable* table);

hashtable_object* create_object(const char* key, node* node);

hashtable* create_table(int size_of_table);

int hash_function(const char* key);

void free_object(hashtable_object* object);

void free_hashtable(hashtable* table);

void collision_prevention(hashtable* table, int index, hashtable_object* object);

void hashtable_insert(hashtable* table, const char* key, node* node);

char* hashtable_search(hashtable* table, const char* key);

hashtable_object* hashtable_search_to_head(hashtable* table, const char* key);

void free_list(list* head);

void free_chains(hashtable* table);

void hashtable_delete(hashtable* table, const char* key);

lru_cache* create_cache(int size_of_cache);

node* create_node(const char* key, const char* value);

void delete_tail(node** head, node** tail);

void add_to_head(node** head, node** tail, const char* key, const char* value);

void cache_insert(lru_cache* cache, const char* key, const char* value);

void free_cache(lru_cache* cache);







