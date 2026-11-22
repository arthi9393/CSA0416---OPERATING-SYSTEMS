
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t wrt;
pthread_mutex_t lock;
int readers=0,data=0;

void *reader(void *x) {
    pthread_mutex_lock(&lock);
    readers++;
    if(readers==1) sem_wait(&wrt);
    pthread_mutex_unlock(&lock);

    printf("Reader reads: %d\n",data);

    pthread_mutex_lock(&lock);
    readers--;
    if(readers==0) sem_post(&wrt);
    pthread_mutex_unlock(&lock);
    return NULL;
}
void *writer(void *x) {
    sem_wait(&wrt);
    data++;
    printf("Writer writes: %d\n",data);
    sem_post(&wrt);
    return NULL;
}
int main() {
    pthread_t r1,r2,w;
    sem_init(&wrt,0,1);
    pthread_mutex_init(&lock,NULL);
    pthread_create(&r1,NULL,reader,NULL);
    pthread_create(&w,NULL,writer,NULL);
    pthread_create(&r2,NULL,reader,NULL);
    pthread_join(r1,NULL);
    pthread_join(r2,NULL);
    pthread_join(w,NULL);
    sem_destroy(&wrt);
    pthread_mutex_destroy(&lock);
    return 0;
}
