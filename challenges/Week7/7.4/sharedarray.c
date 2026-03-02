#include <stdio.h>
#include <pthread.h>
#include <sys/wait.h>
#define ARR_SIZE 100000
#define THREAD_NUM 10
volatile int arr[ARR_SIZE];


void* thread_func(void* arg) {
    (void)arg;
    for(int i = 0; i < ARR_SIZE; i++)
    {
        arr[i] += 1;
    }
    return NULL;
}

int main(void)
{
    pthread_t tids[THREAD_NUM];
    
    //launch
    for (int i = 0; i < THREAD_NUM; i++) {
        pthread_create(&tids[i], NULL, thread_func, NULL);
    }
    
    //join
    for (int i = 0; i < THREAD_NUM; i++) {
        pthread_join(tids[i], NULL);
    }

    //wait
    wait(NULL);

    //print
    for (int i = 0; i < ARR_SIZE; i++) {
        if(arr[i] != THREAD_NUM)
        {
            printf("a[%d] = %d, expected %d\n", i, arr[i], THREAD_NUM);
        }
    }

}