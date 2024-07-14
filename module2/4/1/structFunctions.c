#include "structFunctions.h"

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
        tmp = elm->value;

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
            printf("Контакт %d\n", n++);
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
        printf("Фамилия: %s\n", contact->surname);
        printf("Имя: %s\n", contact->firstname);
        printf("Отчество: %s\n", contact->fathername);
        printf("Место работы: %s\n", contact->place_work);
        printf("Позиция на работе: %s\n", contact->position);
        printf("Электронная почта: %s\n", contact->mail);
        printf("Номер телефона: %s\n", contact->nummer);
        printf("Тег в телеграме: %s\n", contact->telegramProfile);
        printf("Ссылка профиля во Вконтакте: %s\n\n", contact->vkLink);
}

Contact* createContact()
{
    int32_t status;
    Contact* temp = (Contact*)malloc(sizeof( Contact));

    printf("1.Добавить все данные\n"
            "2.Добавить основные данные\n");
    scanf("%d", &status);

    if (status == 2)
    {
        printf("введите фамилию\n");
        scanf("%s", temp->surname);
        printf("введите имя\n");
        scanf("%s", temp->firstname);
        printf("введите отчесвто\n");
        scanf("%s", temp->fathername);
        memset(temp->place_work, 0, sizeof(temp->place_work));
        strcpy(temp->place_work,  "Отсутствует");
        memset(temp->position, 0, sizeof(temp->position));
        strcpy(temp->position,  "Отсутствует");
        memset(temp->mail, 0, sizeof(temp->mail));
        strcpy(temp->mail,  "Отсутствует");
        memset(temp->nummer, 0, sizeof(temp->nummer));
        strcpy(temp->nummer,  "Отсутствует");
        memset(temp->telegramProfile, 0, sizeof(temp->telegramProfile));
        strcpy(temp->telegramProfile,  "Отсутствует");
        memset(temp->vkLink, 0, sizeof(temp->telegramProfile));
        strcpy(temp->vkLink,  "Отсутствует");
    }
    else
    {
        printf("Введите фамилию\n");
        scanf("%s", temp->surname);
        printf("Введите имя\n");
        scanf("%s", temp->firstname);
        printf("Введите отчесвто\n");
        scanf("%s", temp->fathername);
        printf("Введите место работы\n");
        scanf("%s", temp->place_work);
        printf("Введите позицию на работе\n");
        scanf("%s", temp->position);
        printf("Введите почту\n");
        scanf("%s", temp->mail);
        printf("Введите номер телефона\n");
        scanf("%s", temp->nummer);
        printf("Введите тег телеграм профиля\n");
        scanf("%s", temp->telegramProfile);
        printf("Введите ссылку страницы во Вконтакте\n");
        scanf("%s", temp->vkLink);
    }
    system("clear");
    printf("Контакт добавлен\n\n");
    return temp;
}

void editContact(DblLinkedList *list, int32_t index)
{
    int32_t status;
    printf("1.Изменить все данные"
           "2.Изменить основные данные\n");
    scanf("%d", &status);
    system("clear");
    if((index > 0) && (index <= list->size))
    {
        Node *elm = NULL;
        Contact *tmp = NULL;
        elm = getNth(list, index-1);
        if (elm == NULL)
        {
            exit(5);
        }
        tmp = elm->value;
        printf("Новая фамилия\n");
        scanf("%s", tmp->surname);
        printf("Новое имя\n");
        scanf("%s", tmp->firstname);
        printf("Новое отчество\n");
        scanf("%s", tmp->fathername);
        if (status == 2)
        {
            system("clear");
            printf("Данные в контакте %d изменены\n\n", index);
            return;
        }
        else
        {
            printf("Новое место работы\n");
            scanf("%s", tmp->place_work);
            printf("Новая позиция на работе\n");
            scanf("%s", tmp->position);
            printf("Новая почта\n");
            scanf("%s", tmp->mail);
            printf("Новый номер телефона\n");
            scanf("%s", tmp->nummer);
            printf("Новый тег телеграм профиля\n");
            scanf("%s", tmp->telegramProfile);
            printf("Новая ссылка страницу во Вконтакте\n");
            scanf("%s", tmp->vkLink);
            system("clear");
            printf("Данные в контакте %d изменены\n\n", index);
        }

    }
    else
    {
        printf("Такой записи не сущесивует\n\n");
    }
}
