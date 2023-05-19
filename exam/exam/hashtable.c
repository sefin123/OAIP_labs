#include "hashtable.h"

//хэш функция принимающая строку(ключ) и возвращает целое значение 
int hash_function(const char* key) {
	int ascii_sum = 0;
	for (int i = 0; i < strlen(key); i++)
		ascii_sum += key[i];
	return ascii_sum % SIZE_OF_CACHE;
}

//создание объекта 
hashtable_object* create_object(const char* key, node* node) {
	hashtable_object* object = (hashtable_object*)malloc(sizeof(hashtable_object));
	object->node = node;
	object->key = key;
	return object;
}

//создание таблицы 
hashtable* create_table(int size_of_table) {
	hashtable* table = (hashtable*)malloc(sizeof(hashtable));
	table->size = size_of_table;
	table->count = EMPTY_TABLE;
	table->objects = (hashtable**)malloc(size_of_table * sizeof(hashtable_object*));
	for (int i = 0; i < size_of_table; i++)
		table->objects[i] = NULL;
	table->chains = create_chains(table);
	return table;
}

void free_object(hashtable_object* object) {
	free(object->key);
	free(object);
}

void free_hashtable(hashtable* table) {
	hashtable_object* object = NULL;
	for (int i = 0; i < table->size; i++) {
		object = table->objects[i];
		if (object != NULL)
			free_object(object);
	}
	free_chains(table);
	free(table);
}

//ситуация когда различные ключи преобразуются в один и тот же индекс это называется коллизией
void collision_prevention(hashtable* table, int index, hashtable_object* object) {
	list* head = table->chains[index];
	if (head == NULL) {   //если в цепочке по данному индексу уже есть объект с таким же ключом то ее значение обновляется
		head = create_list();
		head->object = object;
		head->next = NULL;
		table->chains[index] = head;
		return;
	}
	else {   //объект добавляется в конец цепочки
		list* current = table->chains[index];
		while (current != NULL) {
			if (!strcmp(current->object->key, object->key)) {
				free(current->object->node->value);
				current->object->node->value = object->node->value;
				return;
			}
			current = current->next;
		}
		table->chains[index] = insert_list(head, object);
		return;
	}
}

//вставка нового объекта в хэш-таблицу 
void hashtable_insert(hashtable* table, const char* key, node* node) {
	hashtable_object* object = create_object(key, node);
	int index = hash_function(key);
	hashtable_object* current_object = table->objects[index];
	if (current_object == NULL) {
		table->objects[index] = object;
		table->count++;
	}
	else {
		if (!strcmp(current_object->key, key)) {  //совпадение ключа(обнавляется значение узла)
			free(current_object->node->value);
			current_object->node->value = node->value;
			return;
		}
		else {
			collision_prevention(table, index, object);  //добавляет новый объект в цепочку
			return;
		}
	}
}

char* hashtable_search(hashtable* table, const char* key) {   //осуществляет поиск значения по ключу в хэш-таблице 
	int index = hash_function(key);
	hashtable_object* current_object = table->objects[index];
	list* head = table->chains[index];
	while (current_object != NULL) {
		if (!strcmp(current_object->key, key))
			return current_object->node->value;
		if (head == NULL)
			return NULL;
		current_object = head->object;
		head = head->next;
	}
	return NULL;
}

hashtable_object* hashtable_search_to_head(hashtable* table, const char* key) {   //осуществляет поиск значения по ключу в хэш-таблице 
	int index = hash_function(key);
	hashtable_object* current_object = table->objects[index];
	list* head = table->chains[index];
	while (current_object != NULL) {
		if (!strcmp(current_object->key, key))
			return current_object;
		if (head == NULL)
			return NULL;
		current_object = head->object;
		head = head->next;
	}
	return NULL;
}

//создание листа 
list* create_list() {
	list* new_list = (list*)malloc(sizeof(list));
	return new_list;
}

//функция предназначена для вставки элемента object в конец списка head
list* insert_list(list* head, hashtable_object* object) {
	if (head == NULL) {
		list* new_list = create_list();
		new_list->object = object;
		new_list->next = NULL;
		head = new_list;
		return new_list;
	}
	else {
		list* temp = head;
		while (temp->next != NULL)
			temp = temp->next;
		list* node = create_list();
		node->object = object;
		node->next = NULL;
		temp->next = node;
		return head;
	}
}

void free_list(list* head) {
	list* temp = NULL;
	if (head == NULL)
		return;
	while (head != NULL) {
		temp = head;
		head = head->next;
		free(temp->object->key);
		free(temp->object->node);
		free(temp->object);
		free(temp);
	}
}

//эта функция создает массив указателей на списки, которые будут использоваться для хранения объектов в случае коллизий
list* create_chains(hashtable* table) {
	list** chains = (list**)malloc(table->size * sizeof(list*));
	for (int i = 0; i < table->size; i++) {
		chains[i] = NULL;
	}
	return chains;
}

void free_chains(hashtable* table) {
	list** chains = table->chains;
	for (int i = 0; i < table->size; i++)
		free_list(chains[i]);
	free(chains);
}

//удаление объектов из таблицы в зависимости от условий 
void hashtable_delete(hashtable* table, const char* key) {
	int index = hash_function(key);
	hashtable_object* object = table->objects[index];
	list* head = table->chains[index];
	if (object == NULL) {
		return;
	}
	else {
		if (!strcmp(object->key, key) && head == NULL) {
			table->objects[index] = NULL;
			table->count--;
			return;
		}
		else if (head != NULL) {
			if (!strcmp(object->key, key)) {
				list* node = head;
				head = head->next;
				node->next = NULL;
				table->objects[index] = create_object(node->object->key, node->object->node);
				table->chains[index] = head;
				return;
			}
			list* current = head;
			list* prev = NULL;
			while (current != NULL) {
				if (!strcmp(current->object->key, key)) {
					if (prev == NULL) {
						table->chains[index] = head->next;
						current->next = NULL;
						return;
					}
					else {
						prev->next = current->next;
						current->next = NULL;
						return;
					}
				}
				prev = current;
				current = current->next;
			}
		}
	}
}

void free_cache(lru_cache* cache) {
	free_hashtable(cache->table);
	free(cache);
}

//эта функция удаляет последний узел в связном списке
void delete_tail(node** head, node** tail) {
	node* temp = (*head);
	if ((*tail) != (*head)) {
		while (temp->next != (*tail))
			temp = temp->next;
		(*tail) = temp;
		(*tail)->next = NULL;
	}
	else {
		(*tail) = NULL;
		(*head) = NULL;
	}
}

//создание нового элемента для двусвязного списка
node* create_node(const char* key, const char* value) {
	node* temp = (node*)malloc(sizeof(node));
	temp->key = key;
	temp->value = value;
	temp->next = NULL;
	temp->prev = NULL;
	return temp;
}

//добавление нового узла в начало двусвязного списка
void add_to_head(node** head, node** tail, const char* key, const char* value) {
	node* temp = create_node(key, value);
	if ((*head) == NULL) {
		(*head) = temp;
		(*tail) = temp;
	}
	else {
		temp->next = (*head);
		(*head)->prev = temp;
		(*head) = temp;
	}
}

//создаем cash:))
lru_cache* create_cache(int size_of_cache) {
	lru_cache* cache = (lru_cache*)malloc(sizeof(lru_cache));
	cache->table = create_table(SIZE_OF_CACHE);
	cache->head = NULL;
	cache->tail = NULL;
	cache->count = EMPTY_TABLE;
	return cache;
}

//удаление и добавление нового элемента cache
void cache_insert(lru_cache* cache, const char* key, const char* value) {
	if (cache->count >= SIZE_OF_CACHE) {
		hashtable_delete(cache->table, cache->tail->key);
		delete_tail(&cache->head, &cache->tail);
	}
	add_to_head(&cache->head, &cache->tail, key, value);
	hashtable_insert(cache->table, key, cache->head);
	cache->count++;
}
