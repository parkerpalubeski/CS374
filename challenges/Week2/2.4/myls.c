#include <unistd.h>
#include <dirent.h>
#include <string.h>

int main(void)
{
    DIR *dir;
    struct dirent *file;

    dir = opendir("/");

    //loop through all subdirectories, returning names
    while((file = readdir(dir))!= NULL)
    {
        write(1, file->d_name, strlen(file->d_name));
        write(1, "\n", 1);
    }
}