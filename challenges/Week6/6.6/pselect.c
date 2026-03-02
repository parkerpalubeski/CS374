#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/select.h>
#define BUFFER_SIZE 128
volatile sig_atomic_t flag;

void sigusr1_handler(int sig)
{
    (void)sig;
    write(1, "SIGUSR1 handled\n", 16);
}


int main(void)
{
    sigset_t sigset, zero;
    fd_set readfds;
    struct sigaction sa = {
        .sa_handler = sigusr1_handler,
        .sa_flags = SA_RESTART,
    };
    char buf[BUFFER_SIZE];
    int re;

    //Handler
    sigaction(SIGUSR1, &sa, NULL);

    //Block
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGUSR1);
    sigprocmask(SIG_BLOCK, &sigset, NULL);

    sigemptyset(&zero);

    FD_ZERO((&readfds));
    FD_SET(0, &readfds); // Set fd 0

    printf("Either enter some text, or...\n");
    printf("go to another window and `kill -USR1 %d`.\n", getpid());

    re = pselect(1, &readfds, NULL, NULL, NULL, &zero);

    if (re == -1 && errno == EINTR && flag) {
        printf("Got SIGUSR1!\n");
    }
    else if(re > 0 && FD_ISSET(0, &readfds))
    {
        int len = read(0, buf, BUFFER_SIZE);
        buf[len] = '\0';
        printf("You typed: %s", buf);
    }
}