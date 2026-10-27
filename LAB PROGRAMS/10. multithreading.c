
#include <stdio.h>
#include <pthread.h>

void *task(void *arg) {
    printf("Thread %d is running\n", *(int *)arg);
    return NULL;
}

int main() {
    pthread_t t[2];
    int a=1,b=2;
    pthread_create(&t[0],NULL,task,&a);
    pthread_create(&t[1],NULL,task,&b);
    pthread_join(t[0],NULL);
    pthread_join(t[1],NULL);
    return 0;
}
