
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int buffer,full=0;
sem_t empty,used;
pthread_mutex_t lock;

void *producer(void *x) {
    for(int i=1;i<=5;i++) {
        sem_wait(&empty);
        pthread_mutex_lock(&lock);
        buffer=i;
        printf("Produced: %d\n",buffer);
        pthread_mutex_unlock(&lock);
        sem_post(&used);
    }
    return NULL;
}
void *consumer(void *x) {
    for(int i=1;i<=5;i++) {
        sem_wait(&used);
        pthread_mutex_lock(&lock);
        printf("Consumed: %d\n",buffer);
        pthread_mutex_unlock(&lock);
        sem_post(&empty);
    }
    return NULL;
}
int main() {
    pthread_t p,c;
    sem_init(&empty,0,1);
    sem_init(&used,0,0);
    pthread_mutex_init(&lock,NULL);
    pthread_create(&p,NULL,producer,NULL);
    pthread_create(&c,NULL,consumer,NULL);
    pthread_join(p,NULL);
    pthread_join(c,NULL);
    sem_destroy(&empty); sem_destroy(&used);
    pthread_mutex_destroy(&lock);
    return 0;
}
