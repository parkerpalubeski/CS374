//Parker Palubeski
//CS 374
//Project 1

#include <unistd.h>
#include <fcntl.h>

#define MAX_LENGTH 2048

int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        int fd = open(argv[1], O_RDWR);
        int len = read(fd, argv[1], MAX_LENGTH);
        write(1, argv[1], len);
        write(1, "\n", 1);
        return close(fd);
    }
    else
    {
        write(2, "Error: readfile.c", 18);
        return 1;
    }
}