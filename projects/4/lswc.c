//Parker Palubeski
//CS 374
//Project 4

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void ls();

int main(int argc, char* argv[])
{
    if(argc > 2){fprintf(stderr, "usage: ./lswc path\n"); exit(1);}
    int pfds[2];
    pipe(pfds);
    int pid = fork();
    if(pid == -1)
    {
        perror("fork");
        exit(1);
    }
    else if(pid > 0)
    {
        dup2(pfds[1], 1);
        close(pfds[0]);
        if(argc == 2)
        {
            //Argument is argv[1]
            ls(argv[1]);
        }
        else if(argc ==1)
        {
            //Argument is "." 
            ls(".");
        }
    }
    else{
        dup2(pfds[0], 0);
        close(pfds[1]);
        execlp("wc", "wc", "-l", NULL);
    }
}

void ls(char* arg)
{
    execlp("ls", "ls", "-1", "-a", arg, NULL);
}