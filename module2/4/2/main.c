#include "structFunctions.h"


int main()
{
    srand(time(NULL));
    const int32_t N = rand() % 25;
    DblLinkedList *queue = createDblLinkedList();
    Node* test;

    for (int32_t i = 0; i < N; i++)
    {
        Node *tmp = (Node*) malloc(sizeof(Node));
        strcpy(tmp->message, "test");
        tmp->priority = rand() % 256;
        pushBack(queue, tmp);
    }
    printDblLinkedList(queue, printListContact);


    if((test = popFront(queue)) != NULL)
    {
        printf("\nПервый элемент\n");
        printListContact(test);
        free(test);
        printf("\n");
    }
    else
    {
        printf("нет элемента\n");
    }

    printDblLinkedList(queue, printListContact);

    int32_t priority;
    printf("Введите приоритет задачи(0-255): ");
    scanf("%d", &priority);
    if((test = popFrontPriority(&queue, priority)) != NULL)
    {
        printf("\nэлемент с указанным приоритетом\n");
        printListContact(test);
        free(test);
    }
    else
    {
        printf("нет элемента\n");
    }

    printf("\n");
    printDblLinkedList(queue, printListContact);

    printf("Введите приоритет задачи(Для задач с приоритетом не меньше заданого 0-255): ");
    scanf("%d", &priority);
    if((test = popFrontPriorityMore(&queue, priority)) != NULL)
    {
        printf("\nэлемент с приоритетом не ниже\n");
        printListContact(test);
        free(test);
    }
    else
    {
        printf("нет элемента\n");
    }

    printf("\n");
    printDblLinkedList(queue, printListContact);


}
