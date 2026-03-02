//Parker Palubeski
//CS 374
//Project 1

#include <fcntl.h>
#include <unistd.h>
#define MAX_LENGTH 2048

int main(int argc, char* argv[]){
    int fd, len;
    char buf[MAX_LENGTH];
    //Case if no arguments are given
    if(argc == 1)
    {
        fd = 0;
        do
        {
            len = read(fd, buf, MAX_LENGTH);
            write(1, buf, len);
        }while(len != 0 && len != -1);
        close(fd);
    }
    //Case if arguments are given
    else if(argc >= 2)
    {
        //Iterate through files
        for(int i = 1; i < argc; i++)
        {
            fd = open(argv[i], O_RDWR);
            len = read(fd, buf, MAX_LENGTH);

            //Break out of the loop if read returns 0 or -1
            if(len == 0 || len == -1)
            {
                break;
            }
            
            write(1, buf, len);
            write(1, "\n", 1);
            close(fd);
        }
    }
}