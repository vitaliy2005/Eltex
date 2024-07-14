#ifndef STRUCT_FUNCTION_H
#define STRUCT_FUNCTION_H

#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

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
void deleteNth(DblLinkedList *list, int32_t index);
Node* getNth(DblLinkedList *list, int32_t index);
Contact* createContact();



// void insertBeforeElement(DblLinkedList *list, Node* elm, Contact *value) {
//     Node *ins = NULL;
//     if (elm == NULL) {
//         exit(6);
//     }

//     if (!elm->prev) {
//         pushFront(list, value);
//         return;
//     }
//     ins = (Node*) malloc(sizeof(Node));
//     ins->value = value;
//     ins->prev = elm->prev;
//     elm->prev->next = ins;
//     ins->next = elm;
//     elm->prev = ins;

//     list->size++;
// }

// void insertionSort(DblLinkedList **list, int (*cmp)(Contact*, Contact*)) {
//     DblLinkedList *out = createDblLinkedList();
//     Node *sorted = NULL;
//     Node *unsorted = NULL;

//     pushFront(out, popFront(*list));

//     unsorted = (*list)->head;
//     while (unsorted) {
//         sorted = out->head;
//         while (sorted && !cmp(unsorted->value, sorted->value)) {
//             sorted = sorted->next;
//         }
//         if (sorted) {
//             insertBeforeElement(out, sorted, unsorted->value);
//         } else {
//             pushBack(out, unsorted->value);
//         }
//         unsorted = unsorted->next;
//     }

//     free(*list);
//     *list = out;
// }

#endif
