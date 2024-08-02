#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <strings.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>


int32_t findSymbol(char* str)
{
    int32_t i = strlen(str);
    while (str[i] != '/' && i != 0) i--;

    return strlen(str) - i;
}

void print_file_type(const char *filename) {
    struct stat file_stat;

    if (stat(filename, &file_stat) != 0) {
        perror("stat error");
        return;
    }

    if (S_ISREG(file_stat.st_mode))
    {
        printf("%s - regular file\n", filename);
    }
    else if (S_ISDIR(file_stat.st_mode))
    {
        printf("%s - directory\n", filename);
    }
    else if (S_ISLNK(file_stat.st_mode))
    {
        printf("%s - symbolic link\n", filename);
    }
    else if (S_ISCHR(file_stat.st_mode))
    {
        printf("%s - character device\n", filename);
    }
    else if (S_ISBLK(file_stat.st_mode))
    {
        printf("%s - block device\n", filename);
    }
    else if (S_ISFIFO(file_stat.st_mode))
    {
        printf("%s - FIFO\n", filename);
    }
    else if (S_ISSOCK(file_stat.st_mode))
    {
        printf("%s - socket\n", filename);
    }
    else
    {
        printf("%s - unknown type\n", filename);
    }
}

void list_directory(const char *path) {
    struct dirent *de;
    DIR *dr = opendir(path);
    char dir[1024];
    char* lpath;
    strcpy(dir, "");
    strcpy(lpath, path);

    if (dr == NULL)
    {
        perror("Could not open directory");
        return;
    }
    while (1)
    {
        while ((de = readdir(dr)) != NULL)
        {
            if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0)
            {
                char full_path[1024];
                snprintf(full_path, sizeof(full_path), "%s/%s", lpath, de->d_name);
                print_file_type(full_path);
            }
        }
        closedir(dr);
        scanf("%s", dir);
        if (strcasecmp(dir, "exit") == 0) break;

        if(strcasecmp(dir, "..") == 0)
        {
            strlcpy(lpath, lpath, strlen(lpath)-findSymbol(lpath)+1);
            dr = opendir(lpath);
        }
        else
        {
            sprintf(lpath, "%s/%s", lpath, dir);
            struct stat file_stat;

            if (stat(lpath, &file_stat) != 0)
            {
                perror("stat error");
                return;
            }
            if(S_ISDIR(file_stat.st_mode))
            {
                dr = opendir(lpath);
            }
            else
            {
                printf("select directory\n");
                strlcpy(lpath, lpath, strlen(lpath)-findSymbol(lpath)+1);
                dr = opendir(lpath);
            }
        }
    }
    closedir(dr);
}

int main(int argc, char *argv[])
{
    list_directory("/home");

    return 0;
}
