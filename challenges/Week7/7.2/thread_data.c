#include <stdio.h>
#include <pthread.h>

void* thread(void* arg) {
    (void)arg;
    char *msg[16] = arg;
    printf("%s", msg[0]);
    printf("%s", msg[1]);
    return NULL;
}

int main() {
    pthread_t tid;
    char msg[2][16] = {"child: hello", "child: goodbye!"};
    printf("parent: hello!\n");
    pthread_create(&tid, NULL, thread, msg);
    pthread_join(tid, NULL);  // Wait for thread to finish
    printf("parent: goodbye!\n");
    return 0;
}