#include "structFunctions.h"
#include <stdio.h>


DblLinkedList* createDblLinkedList()
{
    DblLinkedList *tmp = (DblLinkedList*) malloc(sizeof(DblLinkedList));
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;

    return tmp;
}

void deleteDblLinkedList(DblLinkedList **list)
{
    Node *tmp = (*list)->head;
    Node *next = NULL;
    while (tmp)
    {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
}

void pushFront(DblLinkedList *list, Contact* data)
{
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL)
    {
        exit(1);
    }
    tmp->value = data;
    tmp->next = list->head;
    tmp->prev = NULL;
    if (list->head)
    {
        list->head->prev = tmp;
    }
    list->head = tmp;

    if (list->tail == NULL)
    {
        list->tail = tmp;
    }
    list->size++;
}


Contact* popFront(DblLinkedList *list)
{
    Node *prev;
    Contact *tmp;
    if (list->head == NULL)
    {
        exit(2);
    }

    prev = list->head;
    list->head = list->head->next;
    if (list->head)
    {
        list->head->prev = NULL;
    }
    if (prev == list->tail)
    {
        list->tail = NULL;
    }
    tmp = prev->value;
    free(prev);

    list->size--;
    return tmp;
}

void pushBack(DblLinkedList *list,  Contact* value)
{
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL)
    {
        exit(3);
    }
    tmp->value = value;
    tmp->next = NULL;
    tmp->prev = list->tail;
    if (list->tail)
    {
        list->tail->next = tmp;
    }
    list->tail = tmp;

    if (list->head == NULL)
    {
        list->head = tmp;
    }
    list->size++;
}

Contact* popBack(DblLinkedList *list)
{
    Node *next;
    Contact *tmp;
    if (list->tail == NULL)
    {
        exit(4);
    }

    next = list->tail;
    list->tail = list->tail->prev;
    if (list->tail)
    {
        list->tail->next = NULL;
    }
    if (next == list->head)
    {
        list->head = NULL;
    }
    tmp = next->value;
    free(next);

    list->size--;
    return tmp;
}

Node* getNth(DblLinkedList *list, int32_t index)
{
    Node *tmp = NULL;
    size_t i;

    if (index < list->size/2)
    {
        i = 0;
        tmp = list->head;
        while (tmp && i < index)
        {
            tmp = tmp->next;
            i++;
        }
    }
    else
    {
        i = list->size - 1;
        tmp = list->tail;
        while (tmp && i > index)
        {
            tmp = tmp->prev;
            i--;
        }
    }

    return tmp;
}

void deleteNth(DblLinkedList *list, int32_t index)
{
    if((index > 0) && (index <= list->size))
    {
        Node *elm = NULL;
        Contact *tmp = NULL;
        elm = getNth(list, index-1);
        if (elm == NULL)
        {
            exit(5);
        }
        if (elm->prev)
        {
            elm->prev->next = elm->next;
        }
        if (elm->next)
        {
            elm->next->prev = elm->prev;
        }

        if (!elm->prev)
        {
            list->head = elm->next;
        }
        if (!elm->next)
        {
            list->tail = elm->prev;
        }

        free(elm);

        list->size--;
    }
    else
    {
        system("clear");
        printf("Данного контакта не существует\n");
    }
}

void printDblLinkedList(DblLinkedList *list, void (*fun)(Contact*))
{
    if(list->size != 0)
    {
        Node *tmp = list->head;
        int n = 1;
        while (tmp)
        {
            printf("Сообщение %d\n", n++);
            fun(tmp->value);
            tmp = tmp->next;
        }
        printf("\n");
    }
    else
    {
        system("clear");
        printf("Нет контактов\n\n");
    }

}

void printListContact(struct Contact* contact)
{
    printf("сообщение - %s | приоритет - %d\n", contact->message, contact->priority);
}

Contact* createContact( int32_t priority, char* message)
{

    Contact* temp = (Contact*)malloc(sizeof( Contact));

    temp->priority = priority;
    strcpy(temp->message, message);

    return temp;
}

Contact* popFrontPriority(DblLinkedList **list, int32_t priority)
{
    Node *elm = (*list)->head;
    Node *next = NULL;
    Contact* tmp = NULL;
    while (elm)
    {
        if(elm->value->priority == priority)
        {
            tmp = elm->value;

            if (elm->prev)
            {
                elm->prev->next = elm->next;
            }
            if (elm->next)
            {
                elm->next->prev = elm->prev;
            }


            if (!elm->prev)
            {
                (*list)->head = elm->next;
            }
            if (!elm->next)
            {
                (*list)->tail = elm->prev;
            }

            free(elm);

            (*list)->size--;
            return tmp;
        }
        elm = elm->next;
    }
    printf("Нет задачи с данным приоритетом\n");
    return NULL;
}

Contact* popFrontPriorityMore(DblLinkedList **list, int32_t priority)
{
    Node *elm = (*list)->head;
    Node *next = NULL;
    Contact* tmp = NULL;
    while (elm)
    {
        if(elm->value->priority >= priority)
        {
            if (elm->prev)
            {
                elm->prev->next = elm->next;
            }
            if (elm->next)
            {
                elm->next->prev = elm->prev;
            }
            tmp = elm->value;

            if (!elm->prev)
            {
                (*list)->head = elm->next;
            }
            if (!elm->next)
            {
                (*list)->tail = elm->prev;
            }

            free(elm);

            (*list)->size--;
            return tmp;
        }
        next = elm->next;
        elm = next;
    }
    printf("Нет задачи с данным приоритетом\n");
    return NULL;
}
