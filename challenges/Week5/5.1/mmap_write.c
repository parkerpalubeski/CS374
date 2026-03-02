#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

#define DATA_SIZE 1024

void errorHandle(char* s);

int main(int argc, char* argv[])
{
    if(argc != 4)
    {
        fprintf(stderr, "usage: mmap_write int float \"string\"\n");
        exit(1);
    }
    int num = atoi(argv[1]);
    double flt = atof(argv[2]);
    char* str = argv[3];
    int fd = open("data.dat", O_RDWR|O_CREAT, 0666);
    if(fd == -1)
    {
        errorHandle("open");
    }
    void *data = mmap(NULL, DATA_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(data == MAP_FAILED)
    {
        errorHandle("mmap");
    }
    *(int*)(data) = num;
    *(float*)(data+8) = flt;
    strcpy((char*)(data+16), str);
    if(munmap(data, DATA_SIZE) == -1)
    {
        errorHandle("munmap");
    }
    close(fd);
}

void errorHandle(char* s)
{
    perror(s);
    exit(1);
}