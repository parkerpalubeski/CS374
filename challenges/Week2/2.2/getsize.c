#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
    int i = 1;
    struct stat st;
    if(argc < 2)
    {
        perror("getsize");
    }
    else
    {
        while(i < argc)
        {
            if(stat(argv[i], &st) == -1)
            {
                perror(argv[i]);
            }
            else
            {
                printf("%s: %ld\n", argv[i], st.st_size);
            }
            i++;
        }
    }
}