/* Q30: Thread concepts - (i) create (ii) join (iii) equal (iv) exit (CO2)
   Compile: gcc q30_threads.c -o q30 -pthread */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t t1, t2;

void *worker(void *arg) {
    int n = *(int *)arg;
    printf("Thread %d running, pthread_self() = %lu\n", n, (unsigned long)pthread_self());
    if (pthread_equal(pthread_self(), t1)) printf("  pthread_equal: this thread is t1\n");
    else printf("  pthread_equal: this thread is NOT t1\n");
    if (n == 2) {
        printf("  Thread 2 calling pthread_exit(42)\n");
        pthread_exit((void *)42L);              /* (iv) exit with a status */
    }
    int *result = malloc(sizeof(int));
    *result = n * 100;
    return result;                              /* return value, collected by join */
}

int main(void) {
    int a = 1, b = 2;
    void *ret;

    /* (i) create */
    pthread_create(&t1, NULL, worker, &a);
    pthread_create(&t2, NULL, worker, &b);
    printf("Main: created threads t1 and t2\n");

    /* (iii) equal */
    printf("Main: pthread_equal(t1, t2) = %s\n", pthread_equal(t1, t2) ? "equal" : "not equal");
    printf("Main: pthread_equal(t1, t1) = %s\n", pthread_equal(t1, t1) ? "equal" : "not equal");

    /* (ii) join */
    pthread_join(t1, &ret);
    printf("Main: t1 joined, returned %d\n", *(int *)ret);
    free(ret);
    pthread_join(t2, &ret);
    printf("Main: t2 joined, exit status %ld\n", (long)ret);

    pthread_exit(NULL);   /* main thread exits, process ends when all threads finish */
}
