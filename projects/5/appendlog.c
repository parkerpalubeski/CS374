//Parker Palubeski
//CS 374
//Project 5


#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

#define REC_SIZE 32
#define REC_NUM 1048576
#define HEADER_SIZE (sizeof(int) * 2)
#define FILE_LENGTH (HEADER_SIZE + (REC_SIZE*REC_NUM))

void validate_input(int pairs, char* args[]);
int append_record(int fd, void* data, char* str, int num);
void dumplog(int fd, void* data);

int main(int argc, char* argv[])
{
    //error handle
    validate_input(argc, argv);
    int pairs = (argc-1) / 2;

    //open file
    int fd = open( "data.dat", O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd == -1)
    {
        perror("open");
        exit(1);
    }
    ftruncate(fd, FILE_LENGTH);
    void *data = mmap(NULL, FILE_LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(data == MAP_FAILED)
    {
        perror("mmap");
        exit(1);
    }

    for(int i = 1; i < 1+ 2* pairs; i+=2)
    {
        int num = atoi(argv[i]);
        char* str = argv[i+1];
        for(int j = 0; j < num; j++)
        {
            pid_t pid = fork();
            if(pid == -1)
            {
                perror("fork");
                exit(1);
            }
            else if(pid == 0)
            {
                append_record(fd, data, str, j);
                exit(0);
            }
        }
    }
    while(wait(NULL) > 0);
    dumplog(fd, data);
    if(munmap(data, FILE_LENGTH) == -1)
    {
        perror("munmap");
    }
    close(fd);
}


void validate_input(int pairs, char* args[])
{
    if(((pairs-1)%2)!= 0)
    {
        fprintf(stderr, "usage: ./appendlog count prefix count prefix ...\n");
        exit(1);
    }
    else
    {
        for(int i = 1; i < pairs; i+=2)
        {
            for(long unsigned int j = 0; j < strlen(args[i]); j++)
            {
                if(!isdigit(args[i][j]))
                {
                    fprintf(stderr, "usage: ./appendlog count prefix count prefix ...\n");
                    exit(1);
                }
            }
        }
    }
}

int append_record(int fd, void* data, char* str, int num)
{
    struct flock lock = {
        .l_type=F_WRLCK,
        .l_whence=SEEK_SET,
        .l_start=0,
        .l_len=HEADER_SIZE,
    };

    if(fcntl(fd, F_SETLKW, &lock) == -1)//lock
    {
        perror("fcntl lock header");
        exit(1);
    }

    int offset = *(int*)(data);//get offset
    *(int*)(data) = offset + REC_SIZE;
    *(int*)(data + sizeof(int)) += 1;//increment count
    
    lock.l_type = F_UNLCK;
    if(fcntl(fd, F_SETLK, &lock) == -1)//unlock
    {
        perror("fcntl unlock header");
        exit(1);
    }

    lock.l_start = offset + HEADER_SIZE;
    lock.l_len = REC_SIZE;
    if(fcntl(fd, F_SETLKW, &lock) == -1)//lock entry
    {
        perror("fcntl lock entry");
        exit(1);
    }
    snprintf(str + strlen(str), REC_SIZE - strlen(str), " %d", num);//append num onto end of entry
    strcpy((char*)(data + offset + HEADER_SIZE), str); // copy into log
    lock.l_type = F_UNLCK;
    if(fcntl(fd, F_SETLK, &lock) == -1)//unlock entry
    {
        perror("fcntl unlock entry");
        exit(1);
    }
   return 0;
}

void dumplog(int fd, void* data)
{
    struct flock lock = {
        .l_type=F_WRLCK,
        .l_whence=SEEK_SET,
        .l_start=0,
        .l_len=FILE_LENGTH,
    };
    if(fcntl(fd, F_SETLKW, &lock) == -1)//lock
    {
        perror("fcntl lock header (dumplog)");
        exit(1);
    }
    int count = *(int*)(data+sizeof(int));//get count
    for(int i = 0; i < count; i++)
    {
        printf("%d : %s\n", i, (char*)(data+HEADER_SIZE+(i*REC_SIZE)));
    }
    lock.l_type = F_UNLCK;
    if(fcntl(fd, F_SETLK, &lock) == -1)//unlock entry
    {
        perror("fcntl unlock entry");
        exit(1);
    }
}