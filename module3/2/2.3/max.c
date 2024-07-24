#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


int main(int32_t argc, char* argv[])
{
    int32_t max = -100000000;
    for(int32_t i = 1; i < argc; i++)
    {
        if (atoi(argv[i]) > max)
        {
            max = atoi(argv[i]);
        }
    }
    char m[1024];
    strcpy(m,"");
    sprintf(m, "%d\n", max);
    write(STDOUT_FILENO, m, strlen(m)+1);
    exit(atoi(m));
}
