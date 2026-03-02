#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
    int fd = open("output.txt", O_CREAT|O_TRUNC|O_WRONLY, 0644);
    dup2(fd, 1);
    printf("Testing?\n");
    fflush(stdout);
    close(fd);
}

//Before copying the file descriptor to stdout, you could copy stdout to another file descriptor using dup(), and use that copy