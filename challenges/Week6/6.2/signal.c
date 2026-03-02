#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void sigint_handler(int sig)
{
    (void)sig;
    write(1, "\nGot SIGINT!\n", 13);
}


int main(void)
{
    signal(SIGINT, sigint_handler);
    printf("Program will exit in 10 seconds. Hit ^C!\n");
    printf("%d seconds remaining\n", sleep(10));
    return 0;
}