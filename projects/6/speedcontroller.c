#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/select.h>
volatile sig_atomic_t flag;
volatile sig_atomic_t speed = 0;

void sigusr1_handler(int sig)
{
    (void)sig;
    flag = 1;
}


int main(void)
{
    printf("PID=%d\n", getpid());
    sigset_t sigset, zero;
    fd_set readfds;
    struct sigaction sa = {
        .sa_handler = sigusr1_handler,
        .sa_flags = 0,
    };
    char c;
    int re;

    //Handler
    sigaction(SIGUSR1, &sa, NULL);

    //Block
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGUSR1);
    sigprocmask(SIG_BLOCK, &sigset, NULL);

    sigemptyset(&zero);

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(0, &readfds);

        re = pselect(1, &readfds, NULL, NULL, NULL, &zero);

        if (re == -1 && errno == EINTR && flag) {//reset functionality
            flag = 0;
            speed = 0;
            printf("SIGUSR1! Speed reset to: %d\n", speed);
        }
        else if (re > 0 && FD_ISSET(0, &readfds)) {//increase/decrease speed from stdin
            if (read(0, &c, 1) > 0) {
                if (c == '+') {
                    speed++;
                    printf("increase speed to: %d\n", speed);
                }
                else if (c == '-') {
                    speed--;
                    printf("decrease speed to: %d\n", speed);
                }
                else if (c == 'q') {
                    break;
                }
            }
        }
    }
}