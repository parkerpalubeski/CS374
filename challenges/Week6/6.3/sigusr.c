#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define BUFFER_SIZE 128

void sigusr1_handler(int sig)
{
    (void)sig;
    write(1, "SIGUSR1 handled\n", 16);
}


int main(void)
{
    struct sigaction sa = {
        .sa_handler = sigusr1_handler,
        .sa_flags = SA_RESTART,
    };
    char buf[BUFFER_SIZE];
    sigaction(SIGUSR1, &sa, NULL);
    printf("Reading from the keyboard. But don't type anything\n");
    printf("Go to another window and 'kill -USR1 %d'\n", getpid());
    if(read(0, buf, BUFFER_SIZE) == -1)
    {
        perror("read");
    }
}