#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>


char* retRandIntStr(char* temp)
{

    int32_t randInt = rand();
    sprintf(temp, "%d",  randInt);

    return temp;

}


int main(void)
{
        int32_t fd[2], nbytes;
        pid_t childpid;
        char string[] = "Hello, world!\n";
        char readbuffer[80];

        if (pipe (fd))
        {
            printf("%s\n","Pipe failed");
            return -1;
        }

        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if(childpid == 0)
        {
            srand(time(NULL));

            close(fd[0]);

            int32_t i = 0;
            char temp[64];
            while (i++ < 10)
            {
                retRandIntStr(temp);
                write(fd[1], temp, strlen(temp)+1);
            }
            exit(0);
            close(fd[1]);

        }
        else
        {
            close(fd[1]);
            int32_t i = 0;
            while (i++ < 10)
            {
                nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
                printf("Получено от дочернего процесса: %s\n", readbuffer);
            }
            close(fd[0]);
        }

        return(0);
}
