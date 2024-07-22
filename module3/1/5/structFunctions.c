#include "structFunctions.h"


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
        free(tmp->value);
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
        bubbleSort(list->head);
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
    bubbleSort(list->head);
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

        free(elm->value);
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
        bubbleSort(list->head);
    }
    else
    {
        printf("Такой записи не сущесивует\n\n");
    }
}

int cmp(Contact* a, Contact* b)
{
    if (strcasecmp(a->fathername, b->fathername) < 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void swap(Contact* a, Contact* b)
{
    Contact temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(struct Node* head)
{
    int swapped;
    struct Node* ptr1;
    struct Node* lptr = NULL;

    if (head == NULL)
    {
        return;
    }

    do
    {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr)
        {
            if (cmp(ptr1->value, ptr1->next->value))
            {
                swap(ptr1->value, ptr1->next->value);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}



void readFile(DblLinkedList* list)
{
    int32_t inputFd, numRead;
    char buf[1024];
    strcpy(buf, "");
    Contact* contact;

    inputFd = open("contact.txt", O_RDONLY);
    if (inputFd == -1)
    {
        printf ("Error opening file contact.txt\n");
        return;
    }

    while ((numRead = read(inputFd, buf, 1024)) > 0)
    {
        int32_t i = 0;
        char* line;
	    line = strtok(buf, "\n");
		while (1)
		{
		    if(line == NULL) break;

            if(strcasecmp(line,  "---------") == 0)
            {
                line = strtok(NULL, "\n");
            }
            else
            {
                contact = (Contact*)malloc(sizeof(Contact));

                strcpy(contact->surname, line);
                line = strtok(NULL, "\n");
                strcpy(contact->firstname, line);
                line = strtok(NULL, "\n");
                strcpy(contact->fathername, line);
                line = strtok(NULL, "\n");
                i++;
                if(strcasecmp(line,  "---------") != 0)
                {
                    if(strcasecmp(line,  "Отсутствует") != 0)
                        strcpy(contact->place_work, line);
                    else
                        strcpy(contact->place_work, "Отсутствует");
                    line = strtok(NULL, "\n");


                    if(strcasecmp(line,  "Отсутствует") != 0)
                        strcpy(contact->position, line);
                    else
                        strcpy(contact->position, "Отсутствует");
                    line = strtok(NULL, "\n");

                    if(strcasecmp(line,  "Отсутствует") != 0)
                        strcpy(contact->mail, line);
                    else
                        strcpy(contact->mail, "Отсутствует");
                    line = strtok(NULL, "\n");

                    if(strcasecmp(line,  "Отсутствует") != 0)
                        strcpy(contact->nummer, line);
                    else
                        strcpy(contact->nummer, "Отсутствует");
                    line = strtok(NULL, "\n");

                    if(strcasecmp(line,  "Отсутствует") != 0)
                        strcpy(contact->telegramProfile, line);
                    else
                        strcpy(contact->telegramProfile, "Отсутствует");
                    line = strtok(NULL, "\n");

                    if(strcasecmp(line,  "Отсутствует") != 0)
                        strcpy(contact->vkLink, line);
                    else
                        strcpy(contact->vkLink, "Отсутствует");
                    line = strtok(NULL, "\n");
                    pushBack(list, contact);
                }
                else
                {
                    line = strtok(NULL, "\n");
                    strcpy(contact->place_work, "Отсутствует");
                    strcpy(contact->position, "Отсутствует");
                    strcpy(contact->mail, "Отсутствует");
                    strcpy(contact->nummer, "Отсутствует");
                    strcpy(contact->telegramProfile, "Отсутствует");
                    strcpy(contact->vkLink, "Отсутствует");
                    pushBack(list, contact);
                }
            }
                printf("%s\n", contact->firstname);
		}
    }
    if (close (inputFd ) == -1 )
	{
	   printf ("Ошибка закрытия файла\n");
	}
}

void saveFile(DblLinkedList* list)
{
    int32_t outputFd, openFlags;
    mode_t filePerms ;
    int32_t numRead;
    char buf[1024];
    strcpy(buf, "");

    openFlags = O_CREAT|O_WRONLY|O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

    outputFd = open ("contact2.txt", openFlags, filePerms);
    if (outputFd == -1)
    {
        printf ("Ошибка открытия файла %s\n ", "contact.txt");
        return;
    }

    Node* contact = list->head;

    for (int32_t i = 0; i < list->size; i++)
    {
        strcat(buf, "---------\n");
        strcat(buf, contact->value->surname);
        strcat(buf, "\n");
        strcat(buf, contact->value->firstname);
        strcat(buf, "\n");
        strcat(buf, contact->value->fathername);
        strcat(buf, "\n");
        strcat(buf, contact->value->place_work);
        strcat(buf, "\n");
        strcat(buf, contact->value->position);
        strcat(buf, "\n");
        strcat(buf, contact->value->mail);
        strcat(buf, "\n");
        strcat(buf, contact->value->nummer);
        strcat(buf, "\n");
        strcat(buf, contact->value->telegramProfile);
        strcat(buf, "\n");
        strcat(buf, contact->value->vkLink);
        strcat(buf, "\n");

        printf("%s %d\n", buf, i);
        contact = contact->next;
    }
    strcat(buf, "---------\n");


    if (write (outputFd, buf, strlen(buf)) <= 0)
	{
		printf ("couldn't write whole buffer\n ");
		return;
	}


    if (close (outputFd ) == -1 )
	{
	   printf ("close output error\n");
	}
}
