#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NULL_TERMINATOR '\0'
#define MAX_SIZE_OF_STRING 256
#define FILE_ERROR -2
#define PROGRAMM_ERROR -3
#define NOT_FOUNDED 0
#define WRONG_INPUT 0
#define RIGHT_IP 1
#define IP_COMPONENTS 4
#define MAX_IP_VALUE 255

#define ORIGINAL_DOMAIN_NOT_FOUNDED 0
#define ORIGINAL_DOMAIN_FOUNDED 1
#define TYPE_A_SEARCH 0
#define TYPE_CNAME_SEARCH 1
#define INDENT_FOR_NEWLINE 1
#define INDENT_FOR_SPACE 1

#pragma warning(disable: 4996)

typedef struct hashtable hashtable;

typedef struct lru_cache lru_cache;

typedef enum code {
	TYPE_A = 1,
	TYPE_CNAME = 2
} code;

typedef enum domen_type_length {
	IN_A = 4,
	IN_CNAME = 8
} domen_type_length;

typedef enum menu {
	SEARCH_BY_DOMEN = 1,
	PRINT,
	EXIT
} menu;

FILE* file_open(const char* file_name, const char* mode);

char* input_str();

int type_data_recording(const char* str, const char* ptr);

int check_ip(const char* str);

int choice_domen_type();

void menu_info();

int choice_menu();

void add_database(const char* domen);

int database_search(const char* key, char** domain, char** ip);

char* search_in_cache(lru_cache* cache, const char* key, int flag);

void search_ip(lru_cache* cache);

void print_cache(lru_cache* lru);

void domain_search_by_ip();