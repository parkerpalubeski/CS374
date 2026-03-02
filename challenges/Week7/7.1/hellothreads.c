#include <stdio.h>
#include <pthread.h>

void* thread_func(void* arg) {
    (void)arg;
    printf("child: hello!\n");
    printf("child: goodbye!\n");
    return NULL;
}

int main() {
    pthread_t tid;
    printf("parent: hello!\n");
    pthread_create(&tid, NULL, thread_func, NULL);
    pthread_join(tid, NULL);  // Wait for thread to finish
    printf("parent: goodbye!\n");
    return 0;
}