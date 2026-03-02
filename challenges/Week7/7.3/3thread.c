#include <stdio.h>
#include <pthread.h>
#include <sys/wait.h>

#define THREAD_NUM 3

void* thread_func(void* arg) {
    (void)arg;
    printf("Running\n");
    return NULL;
}

int main() {
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
    printf("Parent complete\n");
    
    return 0;
}