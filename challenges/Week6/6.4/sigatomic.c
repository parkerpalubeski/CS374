#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define BUFFER_SIZE 128

volatile sig_atomic_t sigusr1_happened;

void sigusr1_handler(int sig)
{
    (void)sig;
    sigusr1_happened = 1;
}


int main(void)
{
    struct sigaction sa = {
        .sa_handler = sigusr1_handler,
        .sa_flags = 0,
    };
    sigaction(SIGUSR1, &sa, NULL);
    printf("Go to another window and 'kill -USR1 %d'\n", getpid());
    while(sigusr1_happened == 0){
        sleep(10);
    }
    printf("SIGUSR1 happened!\n");
}