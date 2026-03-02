#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LENGTH 128

int main(void)
{
    char* fifo = "./fifa";
    mkfifo(fifo, 777);
    int fd = open(fifo, O_RDONLY);
    if (fd < 0) {perror ("open"); exit(1);}
    char buf[MAX_LENGTH];
    int len;
    while(1)
    {
        if((len = read(fd, buf, strlen(buf))) > 0){
            write(1, buf, len);
        }
    }
}