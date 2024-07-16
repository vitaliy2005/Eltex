#ifndef STRUCT_FUNCTION_H
#define STRUCT_FUNCTION_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

typedef struct Contact
{

}Contact;

typedef struct Node
{
    char message[256];
    int32_t priority;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct DblLinkedList
{
    int32_t size;
    Node *head;
    Node *tail;
} DblLinkedList;


Node* popFront(DblLinkedList *list);
Node* popFrontPriority(DblLinkedList **list, int32_t priority);
Node* popFrontPriorityMore(DblLinkedList **list, int32_t priority);
void deleteDblLinkedList(DblLinkedList **list);
void printListContact(struct Node* contact);
DblLinkedList* createDblLinkedList();
void printDblLinkedList(DblLinkedList *list, void (*fun)(Node*));
void pushBack(DblLinkedList *list,  Node* tmp);

#endif
