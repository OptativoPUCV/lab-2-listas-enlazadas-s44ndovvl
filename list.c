#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* list = malloc(sizeof(List));
    assert(list != NULL);
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;

    return list;
}

void * firstList(List * list) {
    if(list->head == NULL || list == NULL) return NULL;
    list->current = list->head;
    return list->current->data;
}

void * nextList(List * list) {
    if(list == NULL || list->current == NULL || list->current->next == NULL) return NULL;
    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    if(list->tail == NULL || list == NULL) return NULL;
    list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if(list == NULL || list->current == NULL || list->current->prev == NULL) return NULL;
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node* newNode = createNode(data);
    newNode->next = list->head;
    if (list->head) list->head->prev = newNode;
    else list->tail = newNode;
    list->head = newNode;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    if(list == NULL) return;
    Node* newNode = createNode(data);
    newNode->prev = list->current;
    newNode->next = list->current->next;
    newNode->prev->next = newNode;
    if(newNode->next) newNode->next->prev = newNode;
    else list->tail = newNode;
    
    return;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if(list == NULL || list->current == NULL) return NULL;
    void *dataNode = list->current->data;

    Node* anterior = list->current->prev;
    Node* posterior = list->current->next;
    if(anterior) anterior->next = posterior;
    else list->head = posterior;

    if(posterior) posterior->prev = anterior;
    else list->tail = anterior;

    free(list->current);
    list->current=NULL;

    return dataNode;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}