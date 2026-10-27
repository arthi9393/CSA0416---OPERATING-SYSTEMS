
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t f[5];

void *philosopher(void *arg) {
    int i=*(int *)arg;
    int a=i, b=(i+1)%5;
    if(a>b){int t=a;a=b;b=t;}
    pthread_mutex_lock(&f[a]);
    pthread_mutex_lock(&f[b]);
    printf("Philosopher %d is eating\n",i);
    sleep(1);
    pthread_mutex_unlock(&f[b]);
    pthread_mutex_unlock(&f[a]);
    printf("Philosopher %d is thinking\n",i);
    return NULL;
}

int main() {
    pthread_t t[5];
    int i,id[5];
    for(i=0;i<5;i++) pthread_mutex_init(&f[i],NULL);
    for(i=0;i<5;i++){
        id[i]=i;
        pthread_create(&t[i],NULL,philosopher,&id[i]);
    }
    for(i=0;i<5;i++) pthread_join(t[i],NULL);
    for(i=0;i<5;i++) pthread_mutex_destroy(&f[i]);
    return 0;
}
