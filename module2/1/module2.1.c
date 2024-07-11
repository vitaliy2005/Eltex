#include "structFunctions.h"

int32_t size = 0;

void menu()
{
    printf("Список действий с базой данных контактов: \n"
            "1 - вывести всех на экран\n"
            "2 - добавить контакт\n"
            "3 - удалить контакт\n"
            "4 - изменить контакт\n"
            "0 - выйти из программы\n");
}

int main()
{
    int32_t status;
    struct Contact* contacts = NULL;

    while (status != 0)
    {
        menu();
        scanf("%d", &status);

        switch (status)
            {
                case 1:
                {
                    system("clear");
                    printListContacts(contacts);
                    break;
                }
                case 2:
                {
                    system("clear");
                    contacts = addContact(contacts);
                    break;
                }
                case 3:
                {
                    system("clear");
                    int32_t n;
                    printf("Какой контакт удалить?\n");
                    scanf("%d", &n);
                    contacts = deleteContact(contacts, n);
                    break;
                }
                case 4:
                {
                    system("clear");
                    int32_t n;
                    printf("Какой контакт изменить?\n");
                    scanf("%d", &n);
                    editContact(contacts, n);
                    break;
                }
                case 0:
                {
                    free(contacts);
                    system("clear");
                    break;
                }
                default:
                    system("clear");
                    break;
            }
    }

    return 0;
}
