#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>

#define COUNT 1000

void *thread_function(void *arg)
{
    (void)arg;
    return NULL;
}

double elapsed(struct timespec start, struct timespec end)
{
    return (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec) / 1000000000.0;
}

int main(void)
{
    pid_t pids[COUNT];
    pthread_t threads[COUNT];
    struct timespec start, end;
    int i;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (i = 0; i < COUNT; i++) {
        pids[i] = fork();

        if (pids[i] < 0) {
            perror("fork");
            return 1;
        }

        if (pids[i] == 0)
            _exit(0);
    }

    for (i = 0; i < COUNT; i++) {
        if (waitpid(pids[i], NULL, 0) < 0) {
            perror("waitpid");
            return 1;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Time for 1000 processes: %.6f seconds\n",
           elapsed(start, end));

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (i = 0; i < COUNT; i++) {
        int result = pthread_create(&threads[i], NULL,
                                    thread_function, NULL);
        if (result != 0) {
            fprintf(stderr, "pthread_create failed: %d\n", result);
            return 1;
        }
    }

    for (i = 0; i < COUNT; i++) {
        int result = pthread_join(threads[i], NULL);
        if (result != 0) {
            fprintf(stderr, "pthread_join failed: %d\n", result);
            return 1;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Time for 1000 threads: %.6f seconds\n",
           elapsed(start, end));

    return 0;
}
