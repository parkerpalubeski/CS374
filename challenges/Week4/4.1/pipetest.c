
#define SIZE 6
#include <unistd.h>
#include <stdio.h>


int main(void)
{
    int pfds[2];
    pipe(pfds);
    char buf[SIZE];

    write(pfds[1], "Hello\n", SIZE);
    write(1, buf, read(pfds[0], buf, SIZE));
}