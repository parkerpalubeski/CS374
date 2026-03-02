#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_COUNT 4

int shared_value = 1;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *run(void *arg)
{
    (void)arg;
        
    pthread_mutex_lock(&mutex);
    if (shared_value > 0) {
        usleep(1);
        shared_value--;
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(void)
{
    pthread_t threads[THREAD_COUNT];

    for (int i = 0; i < THREAD_COUNT; i++)
        pthread_create(threads + i, NULL, run, NULL);

    for (int i = 0; i < THREAD_COUNT; i++)
        pthread_join(threads[i], NULL);

    if (shared_value < 0)
        printf("How'd shared_value get to be %d?\n", shared_value);
    else
        puts("OK");
}

//The program runs 4 threads. Can the problem also manifest with only 2 threads? What about only 1 thread?
//The problem can definitely show up with 2 threads, though its simply less likely. It will not occur with 1 thread because its a race condition.

//Explain exactly what steps threads must individually take for shared_value to fall below 0.
//The validation and writing action in run() aren't atomic, so their actions can interleave between threads
//With 2 threads:
//shared_value = 1
//Thread 1 reads shared_value as 1 into memory
//Thread 2 also reads shared_value 1 into memory
//Thread 1 and 2 both validate in order, but only what they have in their own memory
//Both see 1, so both subtract 1 from shared_value
//shared_value is now -1