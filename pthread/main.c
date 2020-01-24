#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* task(void* argv) {
    printf("Hello from Thread!\n");
    sleep(2);
    return NULL;
}

int main(void) {
    pthread_t tid;

    if (pthread_create(&tid, NULL, &task, NULL)) perror("pthread_create failed");
    printf("main waits for thread to finish\n");
    if (pthread_join(tid, NULL)) perror("pthread_join failed");
    printf("thread is ready\n");
    return 0;
}
