#ifndef STRUCT_FUNCTION_H
#define STRUCT_FUNCTION_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

typedef struct Contact
{
    char message[256];
    int32_t priority;
}Contact;

typedef struct Node
{
    Contact* value;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct DblLinkedList
{
    int32_t size;
    Node *head;
    Node *tail;
} DblLinkedList;

Contact* popFront(DblLinkedList *list);
Contact* popFrontPriority(DblLinkedList **list, int32_t priority);
Contact* popFrontPriorityMore(DblLinkedList **list, int32_t priority);
void deleteDblLinkedList(DblLinkedList **list);
void printListContact(struct Contact*);
DblLinkedList* createDblLinkedList();
void printDblLinkedList(DblLinkedList *list, void (*fun)(Contact*));
void pushBack(DblLinkedList *list,  Contact* value);
Contact* createContact( int32_t priority, char* message);

#endif
