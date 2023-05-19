#include "function.h"
#include "hashtable.h"

//ввод строки
char* input_str() {
	char* string = (char*)calloc(MAX_SIZE_OF_STRING, sizeof(char));
	gets_s(string, MAX_SIZE_OF_STRING);
	int size = strlen(string);
	string = (char*)realloc(string, size + 1);
	return string;
}

//проверка на ввод значений IP
int check_ip(const char* str) {
	if (str == NULL) {
		return WRONG_INPUT;
	}
	int arr[IP_COMPONENTS];
	int counter = sscanf(str, "%d.%d.%d.%d", &arr[0], &arr[1], &arr[2], &arr[3]);
	if (counter != IP_COMPONENTS) {
		return WRONG_INPUT;
	}
	for (int i = 0; i < IP_COMPONENTS; i++) {
		if (arr[i] < 0 || arr[i] > MAX_IP_VALUE) {
			return WRONG_INPUT;
		}
	}
	return RIGHT_IP;
}

//меню выбора 
int choice_menu() {
	int choice = 0;
	while (scanf_s("%d", &choice) == 0 || choice < 1 || choice > 4 || getchar() != '\n') {
		printf("\nWRONG INPUT: You need to pick 1 - 4: ");
		rewind(stdin);
	}
	return choice;
}

//выбор типа домена 1 - A, 2 - CNAME
int choice_domen_type() {
	int choice = 0;
	while (scanf_s("%d", &choice) == 0 || choice < 1 || choice > 2 || getchar() != '\n') {
		printf("\nYou need to pick 1 or 2: ");
		rewind(stdin);
	}
	return choice;
}

//вид записи данных(A/CNAME)
int type_data_recording(const char* string, const char* mode) {
	int i = 0;
	int j = 0;
	int searched_index = 0;
	for (i = 0; string[i] != NULL_TERMINATOR; i++) {
		j = 0;
		searched_index = i;
		while (mode[j] != NULL_TERMINATOR && string[searched_index] == mode[j]) {
			searched_index++;
			j++;
		}
		if (mode[j] == NULL_TERMINATOR) {
			return searched_index;
		}
	}
	return NOT_FOUNDED;
}

//открытие файла
FILE* file_open(const char* file_name, const char* mode) {
	FILE* file = NULL;
	errno_t error;
	error = fopen_s(&file, file_name, mode);
	if (error != 0) {
		exit(FILE_ERROR);
	}
	return file;
}

void menu_info() {
	printf("\n");
	printf("1 - Search IP by domain\n");
	printf("2 - Print cache\n");
	printf("3 - search domain by ip\n");
	printf("4 - Exit\n");
	printf("Your choice: ");
}

//функци€ выполн€ет поиск домена и соответствующего ему IP - адреса в файле базы данных
int database_search(const char* key, char** domain, char** ip) {
	char* string = (char*)malloc(MAX_SIZE_OF_STRING);
	char* domain_name = (char*)malloc(MAX_SIZE_OF_STRING);
	char* ip_adress = (char*)malloc(MAX_SIZE_OF_STRING);
	int index = 0;
	int indentation_count = 0;
	int type = 0;
	int domain_type = 0;
	FILE* file = file_open("database.txt", "r");
	while (!feof(file)) {
		fgets(string, MAX_SIZE_OF_STRING, file);
		index = type_data_recording(string, "IN A");
		type = IN_A;
		domain_type = TYPE_A;
		if (index == NOT_FOUNDED) {
			index = type_data_recording(string, "IN CNAME");
			type = IN_CNAME;
			domain_type = TYPE_CNAME;
		}
		fseek(file, 0 + indentation_count, SEEK_SET);
		fgets(domain_name, index - type, file);

		fseek(file, index + indentation_count + INDENT_FOR_SPACE, SEEK_SET);
		fgets(ip_adress, MAX_SIZE_OF_STRING, file);

		indentation_count += strlen(string) + INDENT_FOR_NEWLINE;
		if (!strcmp(key, domain_name)) {
			(*domain) = domain_name;
			(*ip) = ip_adress;
			(*ip)[strcspn((*ip), "\n")] = NULL_TERMINATOR; //strcspn удал€ет символ перевода строки
			fclose(file);
			return domain_type;
		}
	}
	free(string);
	fclose(file);
	return NOT_FOUNDED;
}

//поиск зачений в  ЁЎ≈ на основе ключа
char* search_in_cache(lru_cache* cache, const char* key, int flag) {
	char* check = NULL;
	char* result = NULL;
	char* hashtable_result = hashtable_search(cache->table, key);
	if (hashtable_result != NULL) {
		if (check_ip(hashtable_result) == RIGHT_IP && flag == TYPE_A_SEARCH) {
			printf("\nHIT\n");
			return hashtable_result;
		}
		else {
			return hashtable_result;
		}
	}
	else {
		if (flag == TYPE_A_SEARCH)
			printf("\nMISS\n");
		char* domain = NULL;
		char* ip_adress = NULL;
		int database_search_result = database_search(key, &domain, &ip_adress);
		if (database_search_result == NOT_FOUNDED) {
			printf("\nError. No such domen\n");
			printf("Create new domain and IP-adress:\n");
			add_database(key);
			return;
		}
		else if (database_search_result == TYPE_CNAME) {
			flag = TYPE_CNAME_SEARCH;
			if ((result = search_in_cache(cache, ip_adress, flag)) != NULL) {
				cache_insert(cache, key, result);
				return result;
			}
		}
		else if (flag == TYPE_CNAME_SEARCH) {
			return ip_adress;
		}
		else {
			cache_insert(cache, domain, ip_adress);
			return ip_adress;
		}
	}
}

void print_cache(lru_cache* lru) {
	node* node = lru->head;
	while (node != NULL) {
		printf("%s - %s\n", node->key, node->value);
		node = node->next;
	}
}

//добавление нового элемента в базу данных
void add_database(const char* domen) {
	FILE* database = file_open("database.txt", "r+");
	char* new_str = NULL;
	fseek(database, 0, SEEK_END);
	fprintf(database, "%s", domen);
	printf("\nType of \"%s\" :\n", domen);
	printf("1 - \"IN A\"\n");
	printf("2 - \"IN CNAME\"\n");
	printf("Your choice: ");
	int choice = choice_domen_type();
	if (choice == TYPE_A) {
		fprintf(database, "%s", " IN A ");
		printf("\nInput IP-adress: ");
		new_str = input_str();
		while (check_ip(new_str) == WRONG_INPUT) {
			printf("\nWrong input try again: ");
			free(new_str);
			new_str = input_str();
		}
	}
	else if (choice == TYPE_CNAME) {
		fprintf(database, "%s", " IN CNAME ");
		printf("\nInput domain: ");
		new_str = input_str();
	}

	fprintf(database, "%s\n", new_str);
	printf("\n");
	fclose(database);
}

void move_to_head(lru_cache* cache, const char* key) {
	int index = hash_function(key);
	hashtable_object* object = hashtable_search_to_head(cache->table, key);
	if (object == NULL) {
		return;
	}
	if (cache->head == object->node) {
		return;
	}
	object->node->prev->next = object->node->next;
	if (object->node->next != NULL) {
		object->node->next->prev = object->node->prev;
	}
	else {
		cache->tail = object->node->prev;
	}
	object->node->next = cache->head;
	cache->head->prev = object->node;
	cache->head = object->node;
	object->node->prev = NULL;
}

//поиск IP по домену 
void search_ip(lru_cache* cache) {
	char* result = NULL;
	char* domain_name = NULL;
	printf("\nInput a domain: ");
	domain_name = input_str();
	result = search_in_cache(cache, domain_name, TYPE_A_SEARCH);
	if (result != NULL) {
		printf("Searched IP-adress: %s\n", result);
		move_to_head(cache, domain_name);
	}
}

//поиск домена по ip
void domain_search_by_ip() {
	char* buffer = (char*)malloc(MAX_SIZE_OF_STRING);
	char* domain = (char*)calloc(MAX_SIZE_OF_STRING, 1);
	char* ip_adress = (char*)calloc(MAX_SIZE_OF_STRING, 1);
	char* searche = (char*)calloc(MAX_SIZE_OF_STRING, 1);
	int flag = 0;
	printf("\nEnter IP-adress: ");
	searche = input_str();
	if (check_ip(searche) != RIGHT_IP) {
		printf("\nWrong IP-adress\n");
		return;
	}
	FILE* database = file_open("database.txt", "r");
	while (!feof(database)) {
		fgets(buffer, MAX_SIZE_OF_STRING, database);
		int len = strcspn(buffer, "\n");
		buffer[len] = NULL_TERMINATOR;
		if (sscanf(buffer, "%s IN A %s", domain, ip_adress) == 2 && flag == ORIGINAL_DOMAIN_NOT_FOUNDED) {
			if (!strcmp(searche, ip_adress)) {
				printf("%s\n", domain);
				flag = ORIGINAL_DOMAIN_FOUNDED;
				searche = realloc(searche, strlen(domain) + 1);
				strcpy_s(searche, strlen(domain) + 1, domain);
			}
		}
		if (sscanf(buffer, "%s IN CNAME %s", domain, ip_adress) == 2 && flag == ORIGINAL_DOMAIN_FOUNDED) {
			if (!strcmp(searche, ip_adress))
				printf("%s\n", domain);
		}
	}
	free(buffer);
	free(domain);
	free(ip_adress);
	free(searche);
	if (flag == ORIGINAL_DOMAIN_NOT_FOUNDED) {
		printf("\nNo one domain is dounded\n");
		return;
	}
	else
		printf("\n");
}