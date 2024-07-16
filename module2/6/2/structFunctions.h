#ifndef STRUCT_FUNCTION_H
#define STRUCT_FUNCTION_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <dlfcn.h>
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

void (*edit)(DblLinkedList*, int32_t);
DblLinkedList* (*createList)();
void (*deleteList)(DblLinkedList**);
void (*printContact)(Contact*);
void (*pprintList)(DblLinkedList*, void (*fun)(Contact*));
void (*ppushBack)(DblLinkedList*,  Contact*);
void (*ppushFront)(DblLinkedList*, Contact*);
Contact* (*ppopFront)(DblLinkedList *list);
void (*ddeleteNth)(DblLinkedList*, int32_t);
Node* (*ggetNth)(DblLinkedList*, int32_t);
Contact* (*ccreateContact)();


#endif
