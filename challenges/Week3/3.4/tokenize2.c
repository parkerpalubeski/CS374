#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char line[1024];

    fgets(line, sizeof line, stdin);

    if(line == NULL){
        perror("tokenize2");
        exit(0);
    }

    char *token;
    int i = 0;
    if ((token = strtok(line, " \n")) != NULL){
        do{
            printf("%d: %s\n", i, token);
            i++;
        }while ((token = strtok(NULL, " \n")) != NULL);
    }
}

//If you weren't using strtok() to eliminate the newline on the string, how might you do it otherwise? (Look up NULL-termination of strings in C.)
//If we didn't use strtok(), we could use iteration to determine the position of the NULL terminator at the end of the string, then move the null terminator to the space before it which would contain the newline character