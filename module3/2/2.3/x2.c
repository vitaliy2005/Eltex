#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>



int main()
{
    char a[1024], m[1024];
    strcpy(m, "");
    strcpy(a, "");

    read(STDIN_FILENO, a, sizeof(a));

    sprintf(m, "%d\n", atoi(a)*2);
    write(STDOUT_FILENO, m, strlen(a)+1);
    exit(atoi(a)*2);
}
