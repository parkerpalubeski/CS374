#include <stdio.h>   // For perror()
#include <fcntl.h>   // For open()
#include <unistd.h>  // For write() and close()

int main(void)
{
    char buf[128];
    // Integer to hold the file descriptior
    int fd;


    //I changed it from "/foo.txt" in the example because I don't do my coursework in the root directory
    fd = open("foo.txt", O_RDONLY);

    if (fd == -1) {
        // If the open fails, print out an error message prepended with
        // "open"
        perror("open");
        return 1;  // Exit with error code 1
    }

    //read the file from fd, output to buf, return number of bytes in buf to bytes_read
    int bytes_read=read(fd, buf, 128);

    //write buf to stdout
    write(1, buf, bytes_read);
    write(1, "\n", 1);

    // Close the file when done
    close(fd);
}