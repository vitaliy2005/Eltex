#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



int main()
{

    FILE *file = fopen("counter_output.txt", "a");
    if (file == NULL)
    {
        perror("Ошибка открытия файла");
        return EXIT_FAILURE;
    }

    int counter = 1;
    while (1)
    {
        fprintf(file, "%d\n", counter++);
        fflush(file);
        sleep(1);
    }

    fclose(file);
    return EXIT_SUCCESS;
}
