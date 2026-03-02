#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if(argc != 2){
        fprintf(stdout, "usage: producer [message]");
        return 1;
    }
    char* fifo = "./fifa";
    if(mkfifo(fifo, 777)==0){
        int fd = open(fifo, O_WRONLY);
        write(fd, argv[1], strlen(argv[1]));
        close(fd);
    }
}