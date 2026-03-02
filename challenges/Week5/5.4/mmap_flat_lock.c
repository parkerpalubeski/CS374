#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>

#define REC_SIZE 16 // bytes
#define REC_COUNT (1024*1024)
#define FILE_SIZE (REC_SIZE * REC_COUNT)
#define MAX_COUNT 20000

/**
 * Add the next record to the region.
 */
void add_next_record(int fd, void *data)
{
    struct flock lock = {
        .l_type=F_WRLCK,
        .l_whence=SEEK_SET,
        .l_start=0,
        .l_len=0,
    };
    if(fcntl(fd, F_SETLKW, &lock) == -1)
    {
        perror("fcntl set");
        exit(1);
    }




    int count = *(int*)(data);
    *(int*)(data+(count*sizeof(int))+sizeof(int)) = count;
    *(int*)(data) += 1;




    lock.l_type = F_UNLCK;
    if(fcntl(fd, F_SETLK, &lock) == -1)
    {
        perror("fcntl setlkw");
        exit(1);
    }
    return;
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

    ftruncate(fd, FILE_SIZE);

    void *data = mmap(NULL, FILE_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

    if (data == NULL) {
        perror("mmap");
        return 2;
    }

    int *count = data;
    int *records = count + 1;
    *count = 0;

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 3;
    }

    // Both parent and child are running here

    for (int i = 0; i < MAX_COUNT; i++) {
        add_next_record(fd, data);
    }

    if (pid != 0) {
        // Parent only
        wait(NULL);

        printf("count = %d\n", *count);

        // *2 because both parent and child added MAX_COUNT
        for (int i = 0; i < MAX_COUNT * 2; i++) {
            if (records[i] != i)
                printf("records[%d] == %d\n", i, records[i]);
        }
    }
    close(fd);
}