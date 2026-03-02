#include <stdio.h>
#include <pthread.h>

#define ELEMENTS 50000000
#define THREADS 4

int a[ELEMENTS] = {0};

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

volatile int spinlock1 = 0;

void lock(void) {
    while (__sync_lock_test_and_set(&spinlock1, 1))
        ;
}

void unlock(void) {
    __sync_synchronize(); // Memory barrier.
    spinlock1 = 0;
}

void *run(void *arg)
{
    (void)arg;

    for (int i = 0; i < ELEMENTS; i++){
        lock();
        a[i]++;
        unlock();
    }

    return NULL;
}

int main(void)
{
    pthread_t thread[THREADS];

    for (int i = 0; i < THREADS; i++)
        pthread_create(thread + i, NULL, run, NULL);

    for (int i = 0; i < THREADS; i++)
        pthread_join(thread[i], NULL);

    int expected = THREADS;

    for (int i = 0; i < ELEMENTS; i++)
        if (a[i] != expected)
            printf("a[%d] = %d, expected %d\n", i, a[i], expected);
}

//Speculate on what accounts for the time difference if the mutexes were inside or outside the loop.
//If the mutexes are placed within the for loop instead of outside, the mutexes have to lock/unlock THREADS*ELEMENTS number of times, instead of THREADS times

//Speculate on what accounts for the speed difference when using the spinlock in part 3.
//The spin lock is slower. I assume this is because the 3 threads that DON'T hold the lock at any given time are all waiting simultaneously, checking constantly for a free lock which takes tons of CPU power when projected over such a large data set.