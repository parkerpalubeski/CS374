
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    struct stat st;

    if(argc != 2)
    {
        fprintf(stderr, "usage: mymakedir dir\n");
    }
    else if(stat(argv[1], &st) == 0)
    {
        perror(argv[1]);
    }
    else
    {
        mkdir(argv[1], 0777);
    }
}