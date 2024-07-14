#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/stat.h>
#include <string.h>

void print_binary_permissions(mode_t mode)
{
    printf("Двоичное представление: ");
    for (int i = 8; i >= 0; i--) {
        printf("%d", (mode >> i) & 1);
        if (i % 3 == 0) {
            printf(" ");
        }
    }
    printf("\n");
}

void print_symbolic_permissions(mode_t mode)
{
    printf("Символьное предствление: ");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}


void print_numeric_permissions(mode_t mode)
{
    printf("Числовое представление прав доступа: %03o\n", mode & 0777);
}

int modify_permissions(mode_t *mode)
{
    char perm[4];
    printf("Введите новые права (пример - 644): ");
    scanf("%s", perm);
    if (strlen(perm) == 3)
    {
        int count = 0;
        for (int32_t i = 0; i < 3; i++)
        {
            if (perm[i] == '0' || perm[i] == '1' ||perm[i] == '2' ||perm[i] == '3' ||perm[i] == '4' ||perm[i] == '5' ||perm[i] == '6' || perm[i] == '7')
                count++;
            else break;
        }
        if(count == 3)
        {
            sscanf(perm, "%o", mode);
            return 1;
        }
        else
        {
            system("clear");
            printf("Система должна быть восмеричой\n");
        }
    }
    else
    {
        printf("Неверный ввод\n");
    }
    return 0;
}

int main()
{
    mode_t mode;
    char filename[256];

    while (1)
    {
        printf("Введите права(пример - rwxr-xr-x или 755): ");
        char perm[11];
        scanf("%s", perm);

        if (strlen(perm) == 9)
        {
            int f = 1;
            mode = 0;
            for (int i = 0; i < 9; i++) {
                if (perm[i] == 'r') mode |= (1 << (8 - i));
                else if (perm[i] == 'w') mode |= (1 << (8 - i));
                else if (perm[i] == 'x') mode |= (1 << (8 - i));
                else if(perm[i] == '-') continue;
                else
                {
                    system("clear");
                    printf("Неправильная текстовая форма записи прав\n");
                    f = 0;
                    break;
                }
            }
            if (f == 1) break;;
        }
        else if (strlen(perm) == 3)
        {
            int count = 0;
            for (int32_t i = 0; i < 3; i++)
            {
                if (perm[i] == '0' || perm[i] == '1' ||perm[i] == '2' ||perm[i] == '3' ||perm[i] == '4' ||perm[i] == '5' ||perm[i] == '6' || perm[i] == '7')
                    count++;
                else break;
            }
            if(count == 3)
            {
                sscanf(perm, "%o", &mode);
                break;
            }
            else
            {
                system("clear");
                printf("Система должна быть восмеричой\n");
            }
        }
        else
        {
            printf("ошибка ввода\n");
            system("clear");
        }
    }

    print_binary_permissions(mode);
    print_symbolic_permissions(mode);
    print_numeric_permissions(mode);

    while(1)
    {
        printf("Введите имя файла: ");
        scanf("%s", filename);

        struct stat file_stat;

        if (stat(filename, &file_stat) == 0)
        {
            printf("Файл: %s\n", filename);
            print_binary_permissions(file_stat.st_mode);
            print_symbolic_permissions(file_stat.st_mode);
            print_numeric_permissions(file_stat.st_mode);
            break;
        }
        else
        {
            printf("Файл не найден.\n");
            continue;
        }
    }
    modify_permissions(&mode);
    printf("Новые права:\n");
    print_binary_permissions(mode);
    print_symbolic_permissions(mode);
    print_numeric_permissions(mode);
}
