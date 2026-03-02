#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define DATA_SIZE (32*1024) // 32 KB
#define RECORD_SIZE 32 // bytes

/**
 * Read the record into the buffer
 */
void read_record(void *data, int record_num, char *buffer)
{
    off_t offset = record_num * RECORD_SIZE;
    strncpy(buffer,(char*)(data+offset), RECORD_SIZE);
}

/**
 * Write the record to the buffer
 */
void write_record(void *data, int record_num, char *buffer)
{
    off_t offset = record_num * RECORD_SIZE;
    strcpy((char*)(data+offset), buffer);
}

///////////////////////////////////////////////////////////
// Understand but don't modify the code below this point //
///////////////////////////////////////////////////////////

/**
 * Different app modes
 */
enum mode {
    MODE_READ,
    MODE_WRITE
};

/**
 * App context
 */
struct context {
    enum mode mode;
    int rec_num;
    char *buf;
};

/**
 * Print a usage message and exit
 */
void usage(void)
{
    fprintf(stderr, "usage: recordfile read rec_num | write rec_num data\n");
    exit(1);
}

/**
 * Parse command line.
 */
void parse_command_line(int argc, char *argv[], struct context *context)
{
    if (argc < 2) usage();

    if (argv[1][0] == 'r') {
        if (argc != 3) usage();

        context->mode = MODE_READ;
        context->rec_num = atoi(argv[2]);

    } else if (argv[1][0] == 'w') {
        if (argc != 4) usage();

        context->mode = MODE_WRITE;
        context->rec_num = atoi(argv[2]);
        strncpy(context->buf, argv[3], RECORD_SIZE);
        context->buf[RECORD_SIZE-1] = '\0';

    } else
        usage();
}

/**
 * Main
 */
int main(int argc, char *argv[])
{
    char buf[RECORD_SIZE] = {0};
    struct context context = { .buf = buf };

    parse_command_line(argc, argv, &context);

    // Open the file
    int fd;

    if ((fd = open("data.dat", O_RDWR|O_CREAT, 0666)) == -1) {
        perror("open");
        return 2;
    }

    if (ftruncate(fd, DATA_SIZE) == -1) {
        perror("ftruncate");
        return 3;
    }

    void *data = mmap(NULL, DATA_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

    if (data == NULL) {
        perror("mmap");
        return 4;
    }

    // Read or write records
    switch (context.mode) {
        case MODE_READ:
            read_record(data, context.rec_num, buf);
            printf("%d: %s\n", context.rec_num, buf);
            break;

        case MODE_WRITE:
            write_record(data, context.rec_num, context.buf);
            break;
    }

    munmap(data, DATA_SIZE);
    close(fd);
}