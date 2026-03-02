#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    signal(SIGINT, SIG_IGN);
    printf("^C locked out for 5 seconds! Try it!\n");
    sleep(5);

    signal(SIGINT, SIG_DFL);
    printf("^C reenabled! Try it!\n");
    sleep(10);


}