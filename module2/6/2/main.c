#include "structFunctions.h"
#include <dlfcn.h>



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
    void* handle = dlopen ("/lib/lib.so", RTLD_LOCAL | RTLD_NOW);
    if (!handle)
    {
        exit(1);
    }
    edit = dlsym(handle, "editContact");
    createList = dlsym(handle, "createDblLinkedList");
    deleteList = dlsym(handle, "deleteDblLinkedList");
    printContact = dlsym(handle, "printListContact");
    pprintList = dlsym(handle, "printDblLinkedList");
    ppushBack = dlsym(handle, "pushBack");
    ppushFront = dlsym(handle, "pushFront");
    ppopFront = dlsym(handle, "popFront");
    ddeleteNth = dlsym(handle, "deleteNth");
    ggetNth = dlsym(handle, "getNth");
    ccreateContact = dlsym(handle, "createContact");
    int32_t status;
    DblLinkedList *list_Contact = createList();

    while (status != 0)
    {
        menu();
        scanf("%d", &status);

        switch (status)
            {
                case 1:
                {
                    system("clear");
                    pprintList(list_Contact, printContact);
                    break;
                }
                case 2:
                {
                    system("clear");
                    Contact *value = ccreateContact();
                    ppushBack(list_Contact,  value);
                    break;
                }
                case 3:
                {
                    system("clear");
                    int32_t n;
                    printf("Какой контакт удалить?\n");
                    scanf("%d", &n);
                    ddeleteNth(list_Contact, n);
                    printf("Контакт удален\n");
                    break;
                }
                case 4:
                {
                    system("clear");
                    int32_t n;
                    printf("Какой контакт изменить?\n");
                    scanf("%d", &n);
                    edit(list_Contact, n);
                    break;
                }
                case 0:
                {
                    deleteList(&list_Contact);
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
