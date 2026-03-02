//Parker Palubeski
//CS 374
//Project 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_SIZE 2048
#define MAX_ARGUMENT 128

void execute(pid_t, char* s[]);
void tokenize(char* line, char* s[]);

int main(void)
{
    char line[MAX_SIZE] = {};
    char *s[MAX_ARGUMENT] = {};
    pid_t pid;

    while(1)
    {
        //int i = 0;
        printf("->");
        //User input
        fgets(line, MAX_SIZE, stdin);

        //Tokenize string
        tokenize(line, s);
        
        if(s[0] == NULL)
        {
            continue;
        }
        if(strcmp(s[0], "exit") == 0)//exit case
        {
            break;
        }
        else if(strcmp(s[0], "cd") == 0)//cd case
        {
            if(s[1] == NULL){
                fprintf(stderr, "cd: no destination\n");
                continue;
            }
            else if(chdir(s[1]) == 0)
            {
                continue;
            }
            else
            {
                perror("chdir");
            }
        }

        pid = fork(); //Fork
        

        execute(pid, s);
    }
}

//Execute commands: use pid to determine if child or parent
void execute(pid_t pid, char *s[])
{
    if(pid == 0)//Child
    {
        execvp(s[0], s);
        perror("execvp");
        exit(1);
    }
    else if(pid > 0)//Parent
    {
        wait(NULL);
    }
    else
    {
        perror("fork");
        exit(1);
    }
}

//Tokenize the string and return by pointer
void tokenize(char* line, char*s[])
{
    int i = 0;
    char* tok = NULL;

    tok = strtok(line, " \n");
    while(tok != NULL && i < MAX_ARGUMENT){
        s[i] = tok;
        tok = strtok(NULL, " \n");
        i++;
    }
    s[i] = NULL;
}

