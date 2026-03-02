#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/file.h>

#define INCREMENTS 100
#define PROCESSES 6
/**
 * Read the value from the file.
 */
int read_val(int fd)
{
    char buf[1024];

    lseek(fd, SEEK_SET, 0);
    int bytes = read(fd, buf, sizeof buf - 1);
    buf[bytes] = '\0';

    int val = 0;
    sscanf(buf, "%d", &val);

    return val;
}

/**
 * Write the value to the file.
 */
void write_val(int fd, int val)
{
    char buf[1024];
    int len = snprintf(buf, sizeof buf, "%d", val);

    lseek(fd, SEEK_SET, 0);
    write(fd, buf, len);
}

/**
 * Spawn a child process and have it increment the counter a bunch of
 * times.
 */
int spawn_child(int fd) {
    struct flock lock = {
        .l_type=F_WRLCK,
        .l_whence=SEEK_SET,
        .l_start=0,
        .l_len=0,
    };
    switch (fork()) {
        case -1:
            return -1;

        case 0:
            // Child process
            for (int i = 0; i < INCREMENTS; i++) {
                lock.l_type = F_WRLCK;
                if(fcntl(fd, F_SETLKW, &lock) == -1)
                {
                    perror("fcntl setlkw");
                    exit(1);
                }
                int val = read_val(fd);
                write_val(fd, val + 1);
                lock.l_type = F_UNLCK;
                if(fcntl(fd, F_SETLKW, &lock) == -1)
                {
                    perror("fcntl unlck");
                    exit(1);
                }
            }

            exit(0);
    }

    return 0;
}

/**
 * Main.
 */
int main(void)
{
    int fd;

    if ((fd = open("data.dat", O_RDWR|O_CREAT, 0666)) == -1) {
        perror("open");
        return 1;
    }

    for (int i = 0; i < PROCESSES; i++) {
        if (spawn_child(fd) == -1) {
            perror("spawn child");
        }
    }

    for (int i = 0; i < PROCESSES; i++) {
        wait(NULL);
    }

    // After all the children have finished, look and see what's in the
    // file.
    lseek(fd, SEEK_SET, 0);
    char buf[1024];
    int count = read(fd, buf, sizeof buf - 1);
    buf[count] = '\0';
    puts(buf);

    close(fd);
}

//When there are no locks in place, the code has multiple child processes reading and writing into memory and the file. The way the program is designed, the intended implementation is that the child processes wait in order until its their turn, however without locks they will all read/write/increment as soon as they are able, with no real order to it.