
#define MAX_LENGTH 16

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int pfds[2];
    pipe(pfds);


    int pid = fork();
    if(pid==-1)
    {
        perror("fork");
        exit(1);
    }
    else if(pid == 0)
    {
        close(pfds[0]);
        write(pfds[1], "Hello, parent!\n", MAX_LENGTH);
        exit(0);
    }
    else
    {
        char buf[MAX_LENGTH];
        close(pfds[1]);
        read(pfds[0], buf, MAX_LENGTH);
        write(1, buf, MAX_LENGTH);
        wait(NULL);
    }
}