#include "structFunctions.h"
#include <stdio.h>



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
    Node* tree = NULL;
    int32_t size = 1;

    while (status != 0)
    {
        menu();
        scanf("%d", &status);
        if(status == 1)
        {
            system("clear");
            if(tree == NULL) printf("Нет контактов\n");
            else preOrder(tree);
        }
        else if(status == 2)
        {
            system("clear");
            if(tree == NULL)
            {
                tree = newNode(size++, createContact());
            }
            else
            {
                tree = insert(tree, size++);
            }
        }
        else if(status == 3)
        {
            int32_t n;
            printf("Какой контакт удалить?\n");
            scanf("%d", &n);
            deleteNode(tree, n);
            printf("Контакт удален\n");
            system("clear");
        }
        else if(status == 4)
        {
            system("clear");
            int32_t n;
            printf("Какой контакт изменить?\n");
            scanf("%d", &n);
            editContact(tree, n);
            system("clear");

        }
        else if (status == 0)
        {
            system("clear");
        }
        else
        {
            system("clear");
        }
    }

    return 0;
}
