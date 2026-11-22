
#include <stdio.h>
#include <pthread.h>

void *task(void *arg) {
    int id = *(int *)arg;

    printf("Thread %d is running.\n", id);

    for (int i = 1; i <= 5; i++) {
        printf("Thread %d: Count = %d\n", id, i);
    }

    printf("Thread %d has finished.\n", id);

    return NULL;
}

int main() {
    pthread_t threads[3];
    int ids[3] = {1, 2, 3};

    printf("Main thread started.\n");

    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, task, &ids[i]);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads have completed.\n");

    return 0;
}
