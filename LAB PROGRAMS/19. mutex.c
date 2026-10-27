
#include <stdio.h>
#include <pthread.h>

int count=0;
pthread_mutex_t lock;

void *task(void *arg) {
    for(int i=0;i<100000;i++) {
        pthread_mutex_lock(&lock);
        count++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}
int main() {
    pthread_t a,b;
    pthread_mutex_init(&lock,NULL);
    pthread_create(&a,NULL,task,NULL);
    pthread_create(&b,NULL,task,NULL);
    pthread_join(a,NULL);
    pthread_join(b,NULL);
    printf("Count = %d\n",count);
    pthread_mutex_destroy(&lock);
    return 0;
}
