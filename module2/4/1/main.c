#include "structFunctions.h"


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
    DblLinkedList *list_Contact = createDblLinkedList();

    while (status != 0)
    {
        menu();
        scanf("%d", &status);

        switch (status)
            {
                case 1:
                {
                    system("clear");
                    printDblLinkedList(list_Contact, printListContact);
                    break;
                }
                case 2:
                {
                    system("clear");
                    Contact *value = createContact();
                    pushBack(list_Contact,  value);
                    break;
                }
                case 3:
                {
                    system("clear");
                    int32_t n;
                    printf("Какой контакт удалить?\n");
                    scanf("%d", &n);
                    deleteNth(list_Contact, n);
                    printf("Контакт удален\n");
                    break;
                }
                case 4:
                {
                    system("clear");
                    int32_t n;
                    printf("Какой контакт изменить?\n");
                    scanf("%d", &n);
                    editContact(list_Contact, n);
                    break;
                }
                case 0:
                {
                    deleteDblLinkedList(&list_Contact);
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
