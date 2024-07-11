#include "structFunctions.h"

extern int32_t size;

void printListContacts(struct Contact* contacts)
{
    if (size != 0)
    {
        int32_t n = 1;
        for (int32_t i = 0; i < size ; i++)
        {
            printf("-- Контакт %d --\n", n++);
            printf("Фамилия: %s\n", contacts[i].surname);
            printf("Имя: %s\n", contacts[i].firstname);
            printf("Отчество: %s\n", contacts[i].fathername);
            printf("Место работы: %s\n", contacts[i].place_work);
            printf("Позиция на работе: %s\n", contacts[i].position);
            printf("Электронная почта: %s\n", contacts[i].mail);
            printf("Номер телефона: %s\n", contacts[i].nummer);
            printf("Тег в телеграме: %s\n", contacts[i].telegramProfile);
            printf("Ссылка профиля во Вконтакте: %s\n\n", contacts[i].vkLink);
        }
    }
    else
    {
        system("clear");
        printf("Нет контактов\n\n");
    }
}

struct Contact* addContact(struct Contact* contacts)
{
    int32_t status;
    struct Contact* temp = (struct Contact*)malloc((size+1)*sizeof(struct Contact));

    printf("1.Добавить все данные\n"
            "2.Добавить основные данные\n");
    scanf("%d", &status);

    if (size != 0)
    {
        for (int32_t i = 0; i < size; i++)
        {
            copyArray(temp[i].fathername, contacts[i].fathername);
            copyArray(temp[i].firstname, contacts[i].firstname);
            copyArray(temp[i].surname, contacts[i].surname);
            copyArray(temp[i].mail, contacts[i].mail);
            copyArray(temp[i].nummer, contacts[i].nummer);
            copyArray(temp[i].vkLink, contacts[i].vkLink);
            copyArray(temp[i].place_work, contacts[i].place_work);
            copyArray(temp[i].position, contacts[i].position);
            copyArray(temp[i].telegramProfile, contacts[i].telegramProfile);
        }

        if (status == 2)
        {
            printf("введите фамилию\n");
            scanf("%s", temp[size].surname);
            printf("введите имя\n");
            scanf("%s", temp[size].firstname);
            printf("введите отчесвто\n");
            scanf("%s", temp[size].fathername);
            memset(temp[size].place_work, 0, sizeof(temp[size].place_work));
            strcpy(temp[size].place_work,  "Отсутствует");
            memset(temp[size].position, 0, sizeof(temp[size].position));
            strcpy(temp[size].position,  "Отсутствует");
            memset(temp[size].mail, 0, sizeof(temp[size].mail));
            strcpy(temp[size].mail,  "Отсутствует");
            memset(temp[size].nummer, 0, sizeof(temp[size].nummer));
            strcpy(temp[size].nummer,  "Отсутствует");
            memset(temp[size].telegramProfile, 0, sizeof(temp[size].telegramProfile));
            strcpy(temp[size].telegramProfile,  "Отсутствует");
            memset(temp[size].vkLink, 0, sizeof(temp[size].telegramProfile));
            strcpy(temp[size].vkLink,  "Отсутствует");
        }
        else
        {
            printf("Введите фамилию\n");
            scanf("%s", temp[size].surname);
            printf("Введите имя\n");
            scanf("%s", temp[size].firstname);
            printf("Введите отчесвто\n");
            scanf("%s", temp[size].fathername);
            printf("Введите место работы\n");
            scanf("%s", temp[size].place_work);
            printf("Введите позицию на работе\n");
            scanf("%s", temp[size].position);
            printf("Введите почту\n");
            scanf("%s", temp[size].mail);
            printf("Введите номер телефона\n");
            scanf("%s", temp[size].nummer);
            printf("Введите тег телеграм профиля\n");
            scanf("%s", temp[size].telegramProfile);
            printf("Введите ссылку страницы во Вконтакте\n");
            scanf("%s", temp[size].vkLink);
        }
        size++;
        free(contacts);
        contacts = temp;
    }
    else
    {
        contacts = (struct Contact*)malloc((size+1)*sizeof(struct Contact));
        if (status == 2)
        {
            printf("введите фамилию\n");
            scanf("%s", contacts->surname);
            printf("введите имя\n");
            scanf("%s", contacts->firstname);
            printf("введите отчесвто\n");
            scanf("%s", contacts->fathername);
            memset(contacts->place_work, 0, sizeof(contacts->place_work));
            strcpy(contacts->place_work,  "Отсутствует");
            memset(contacts->position, 0, sizeof(contacts->position));
            strcpy(contacts->position,  "Отсутствует");
            memset(contacts->mail, 0, sizeof(contacts->mail));
            strcpy(contacts->mail,  "Отсутствует");
            memset(contacts->nummer, 0, sizeof(contacts->nummer));
            strcpy(contacts->nummer,  "Отсутствует");
            memset(contacts->telegramProfile, 0, sizeof(contacts->telegramProfile));
            strcpy(contacts->telegramProfile,  "Отсутствует");
            memset(contacts->vkLink, 0, sizeof(contacts->vkLink));
            strcpy(contacts->vkLink,  "Отсутствует");
        }
        else
        {
            printf("Введите фамилию\n");
            scanf("%s", contacts->surname);
            printf("Введите имя\n");
            scanf("%s", contacts->firstname);
            printf("Введите отчесвто\n");
            scanf("%s", contacts->fathername);
            printf("Введите место работы\n");
            scanf("%s", contacts->place_work);
            printf("Введите позицию на работе");
            scanf("%s", contacts->position);
            printf("Введите почту");
            scanf("%s", contacts->mail);
            printf("Введите номер телефона");
            scanf("%s", contacts->nummer);
            printf("Введите тег телеграм профиля");
            scanf("%s", contacts->telegramProfile);
            printf("Введите ссылку страницы во Вконтакте");
            scanf("%s", contacts->vkLink);
        }
        size++;
    }
    system("clear");
    printf("Контакт добавлен\n\n");
    return contacts;
}

struct Contact* deleteContact(struct Contact* contacts, int32_t n)
{
    if (n > 0 && n <= size)
    {
        struct Contact* temp = (struct Contact*)malloc((size-1)*sizeof(struct Contact));
        if (size != 0)
        {
            int32_t j = 0;
            for (int32_t i = 0; i < size; i++)
            {
                if (i == n-1) continue;

                copyArray(temp[j].fathername, contacts[i].fathername);
                copyArray(temp[j].firstname, contacts[i].firstname);
                copyArray(temp[j].surname, contacts[i].surname);
                copyArray(temp[j].mail, contacts[i].mail);
                copyArray(temp[j].nummer, contacts[i].nummer);
                copyArray(temp[j].vkLink, contacts[i].vkLink);
                copyArray(temp[j].place_work, contacts[i].place_work);
                copyArray(temp[j].position, contacts[i].position);
                copyArray(temp[j++].telegramProfile, contacts[i].telegramProfile);
            }
            size--;
            free(contacts);
            contacts = temp;
            system("clear");
            printf("Контакт %d удален\n", n);
        }
        else
        {
            free(temp);
            system("clear");
            printf("Нет контактов\n");
        }
    }
    else
    {
        printf("Контакта не сущестует\n\n");
    }

    return contacts;
}

void editContact(struct Contact* contacts, int32_t n)
{
    int32_t status;
    printf("1.Изменить все данные"
           "2.Изменить основные данные");
    scanf("%d", &status);
    system("clear");
    if (n > 0 && n <= size)
    {
        printf("Новая фамилия\n");
        scanf("%s", contacts[n-1].surname);
        printf("Новое имя\n");
        scanf("%s", contacts[n-1].fathername);
        printf("Новое отчество\n");
        scanf("%s", contacts[n-1].fathername);
        if (status == 2)
        {
            system("clear");
            printf("Данные в контакте %d изменены\n\n", n);
            return;
        }
        else
        {
            printf("Новое место работы\n");
            scanf("%s", contacts[n-1].place_work);
            printf("Новая позиция на работе\n");
            scanf("%s", contacts[n-1].position);
            printf("Новая почта\n");
            scanf("%s", contacts[n-1].mail);
            printf("Новый номер телефона\n");
            scanf("%s", contacts[n-1].nummer);
            printf("Новый тег телеграм профиля\n");
            scanf("%s", contacts[n-1].telegramProfile);
            printf("Новая ссылка страницу во Вконтакте\n");
            scanf("%s", contacts[n-1].vkLink);
            system("clear");
            printf("Данные в контакте %d изменены\n\n", n);
        }

    }
    else
    {
        printf("Такой записи не сущесивует\n\n");
    }
}

void copyArray(char *source, char *destination)
{
    for (int i = 0; i < 40; i++)
    {
        source[i] = destination[i];
    }
}
