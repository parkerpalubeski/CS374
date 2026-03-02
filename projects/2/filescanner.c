//Parker Palubeski
//CS 374
//Project 2: Filescanner

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PATHNAME 512

int print_dir(char* dir);


int main(int argc, char* argv[])
{
    if(argc == 1)
    {
        print_dir(".");
    }
    else if(argc > 2)
    {
        //print error if no arguments
        write(1, "usage: filescanner [directory]\n", 30);
        return 1;
    }
    else
    {
        print_dir(argv[1]);
    }
}

int print_dir(char* dirname)
{
    DIR *dir;
    struct dirent *file;
    struct stat st;
    int total = 0;

    if(stat(dirname, &st) != 0)
    {
        perror(dirname);
        exit(1);
    }

    dir = opendir(dirname);
    //Loop, ignoring non-files/directories
    while((file = readdir(dir))!= NULL)
    {
        //Special case for . and ..
        if(strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0){
            continue;
        }
        char path[MAX_PATHNAME];
        snprintf(path, sizeof(path), "%s/%s", dirname, file->d_name);
        //Directory case
        if(file->d_type == DT_DIR)
        {
            total += print_dir(path);
        }
        //Regular file case
        else if(file->d_type == DT_REG)
        {
            if(stat(path, &st) == 0)
            {
                total += st.st_size;
            }
            else
            {
                perror(path);
            }
        }
        //Ignore all other file types
        else
        {
            continue;
        }
    }
    printf("%s: %d\n", dirname, total);
    return total;
}