#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

#define DATA_SIZE 1024

void errorHandle(char* s);

int main(void)
{
    int fd = open("data.dat", O_RDONLY, 0666);
    if(fd == -1)
    {
        errorHandle("open");
    }
    void *data = mmap(NULL, DATA_SIZE, PROT_READ, MAP_SHARED, fd, 0);
    if(data == MAP_FAILED)
    {
        errorHandle("mmap");
    }
    int num = *(int*)(data);
    double flt = *(float*)(data+8);
    char* str = (char*)(data+16);
    printf("Read: %d, %lf, %s\n", num, flt, str);
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