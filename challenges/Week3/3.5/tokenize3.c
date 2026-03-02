#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    // Define the tokens array
    char *tokens[128] = {0};
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
            tokens[i] = token;
            i++;
        }while ((token = strtok(NULL, " \n")) != NULL);
    }
    // Prints out the tokens
    for (int i = 0; tokens[i] != NULL; i++)
        printf("%d: %s\n", i, tokens[i]);

}

//If we didn't initialize the array tokens to be full of NULL pointers, where might the program fail?
//If the array didn't have NULL pointers to start, the array will be full of garbage values instead of NULL and all of those that aren't later filled by the user's input will be printed as well