//Parker Palubeski
//CS 374
//Project 4

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    char **args = argv + 2;
    if(argc < 3)
    {
        fprintf(stderr, "usage: redirout filename command [arg1 [arg2 ...]]\n");
        exit(1);
    }
    else
    {
        int fd = open(argv[1], O_CREAT|O_TRUNC|O_WRONLY, 0666);
        if(fd == -1){
            perror("open");
            close(fd);
            exit(1);
        }
        if(dup2(fd, 1) == -1)
        {
            perror("dup2");
            close(fd);
            exit(1);
        };
        close(fd);
        execvp(args[0], args);
        perror("execvp");
    }
}