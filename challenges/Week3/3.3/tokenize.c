#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    (void)argc;

    if(argc != 2){
        perror("token");
        exit(0);
    }

    char *token;
    int i = 0;
    if ((token = strtok(argv[1], " ")) != NULL){
        do{
            printf("%d: %s\n", i, token);
            i++;
        }while ((token = strtok(NULL, " ")) != NULL);
    }
}

//Why do pass a pointer to the string on the first call to strtok() and NULL later?

//We pass NULL later so that the function can continue to tokenize the original string rather than the token from past runs of the function

//If we passed the pointer repeatedly instead of NULL, it would simply tokenize the token again (meaning we wouldn't do anything because its already tokenized based on the parameters)