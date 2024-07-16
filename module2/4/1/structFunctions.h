#ifndef STRUCT_FUNCTION_H
#define STRUCT_FUNCTION_H

#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <bits/types/siginfo_t.h>

typedef struct Contact
{
    char surname[40];
    char firstname[40];
    char fathername[40];

    char place_work[40];
    char position[40];

    char nummer[40];
    char mail[40];
    char vkLink[40];
    char telegramProfile[40];
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

void editContact(DblLinkedList *list, int32_t index);
void deleteDblLinkedList(DblLinkedList **list);
void printListContact(struct Contact*);
DblLinkedList* createDblLinkedList();
void printDblLinkedList(DblLinkedList *list, void (*fun)(Contact*));
void pushBack(DblLinkedList *list,  Contact* value);
void pushFront(DblLinkedList *list, Contact* data);
Contact* popFront(DblLinkedList *list);
void deleteNth(DblLinkedList *list, int32_t index);
Node* getNth(DblLinkedList *list, int32_t index);
Contact* createContact();
void bubbleSort(struct Node* head);
void swap(Contact* a, Contact* b);
int cmp(Contact* a, Contact* b);

#endif
