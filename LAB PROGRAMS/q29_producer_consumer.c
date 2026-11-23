/* Q29: Classical process synchronization problem (CO2)
   Producer-Consumer (bounded buffer) using semaphores + mutex,
   followed by Dining Philosophers using mutexes. Compile: gcc q29_*.c -o q29 -pthread */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUF 5
#define ITEMS 10

int buffer[BUF], in = 0, out = 0;
sem_t empty, full;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *producer(void *arg) {
    (void)arg;
    for (int i = 1; i <= ITEMS; i++) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = i; printf("Producer produced item %d at slot %d\n", i, in);
        in = (in + 1) % BUF;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        usleep(100000);
    }
    return NULL;
}
void *consumer(void *arg) {
    (void)arg;
    for (int i = 1; i <= ITEMS; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buffer[out]; printf("    Consumer consumed item %d from slot %d\n", item, out);
        out = (out + 1) % BUF;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        usleep(200000);
    }
    return NULL;
}

#define N 5
pthread_mutex_t fork_m[N];
void *philosopher(void *arg) {
    int id = *(int *)arg, l = id, r = (id + 1) % N;
    int first = l < r ? l : r, second = l < r ? r : l;   /* ordered locking avoids deadlock */
    for (int round = 0; round < 2; round++) {
        printf("Philosopher %d is thinking\n", id);
        usleep(50000);
        pthread_mutex_lock(&fork_m[first]);
        pthread_mutex_lock(&fork_m[second]);
        printf("Philosopher %d is eating\n", id);
        usleep(100000);
        pthread_mutex_unlock(&fork_m[second]);
        pthread_mutex_unlock(&fork_m[first]);
    }
    return NULL;
}

int main(void) {
    pthread_t p, c;
    printf("===== Producer-Consumer Problem =====\n");
    sem_init(&empty, 0, BUF);
    sem_init(&full, 0, 0);
    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);
    pthread_join(p, NULL);
    pthread_join(c, NULL);
    sem_destroy(&empty); sem_destroy(&full);

    printf("\n===== Dining Philosophers Problem =====\n");
    pthread_t ph[N]; int id[N];
    for (int i = 0; i < N; i++) pthread_mutex_init(&fork_m[i], NULL);
    for (int i = 0; i < N; i++) { id[i] = i; pthread_create(&ph[i], NULL, philosopher, &id[i]); }
    for (int i = 0; i < N; i++) pthread_join(ph[i], NULL);
    return 0;
}
