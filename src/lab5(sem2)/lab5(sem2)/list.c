#include "list.h"

bool empty(List *self) {
    return self->head == NULL && self->tail == NULL;
}

void pushFront(List* self, Data data)
{
    Node* new = initNode(malloc(sizeof(*new)), data);
    pushNodeFront(self, new);
}

void pushNodeFront(List *self, Node *new) {
    if (empty(self)) {
        self->head = self->tail = new;
        return;
    }

    insertNodeBefore(self->head, new);
    self->head = new;
}

void pushNode(List *self, Node *new) {
    if (empty(self)) {
        self->head = self->tail =  new;
        return;
    }

    insertNodeAfter(self->tail, new);
    self->tail = new;
}

List *initList(List *self) {
    *self = (List) {.head = NULL, .tail = NULL};
    return self;
}

void insertNodeAfter(Node *that, Node *new) {
    new->next = that->next;
    new->prev = that;

    that->next = new;
    if (new->next) new->next->prev = new;
}

void insertNodeBefore(Node* that, Node* new) {
    new->next = that;
    new->prev = that->prev;

    that->prev = new;
    if (new->prev) new->prev->next = new;
}

void freeNode(Node *what) {
    if (!what) return;

    if (what->next) what->next->prev = what->prev;
    if (what->prev) what->prev->next = what->next;

    free(what);
}

void printList(List list) {
    List* tmp = &list;

    if (tmp->head == NULL) return;

    while (tmp->head != NULL) {
        printf("domain:%s ip:%s", tmp->head->data.key, tmp->head->data.value);
        printf("\n");
        tmp->head = tmp->head->next;
    }
}

void detachFromList(List *self, Node *what) {
    if (self->head == what) self->head = what->next;
    if (self->tail == what) self->tail = what->prev;

    if (what->next) what->next->prev = what->prev;
    if (what->prev) what->prev->next = what->next;

    what->next = NULL;
    what->prev = NULL;
}

Node *initNode(Node *self, Data data) {
    *self = (Node) {
            .data = data,
            .next = NULL,
            .prev = NULL,
    };
    return self;
}