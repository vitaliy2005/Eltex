#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>




int main()
{

    int randomNumber = rand() % 100;
    int32_t outputFd, openFlags;
    mode_t filePerms ;
    int32_t numRead;
    char buf[1024];
    strcpy(buf, "");

    openFlags = O_CREAT|O_WRONLY|O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

    outputFd = open("counter_output.txt", openFlags, filePerms);
    if (outputFd == -1)
    {
        printf ("Ошибка открытия файла %s\n ", "counter_output.txt");
        return -1;
    }

    int counter = 1;
    while (1)
    {
        sprintf(buf, "%d\n", counter);
        write(outputFd, buf, strlen(buf)+1);
        sleep(1);
    }

    return EXIT_SUCCESS;
}
