
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int shmid;
    char *shared_memory;
    pid_t pid;

    shmid = shmget(IPC_PRIVATE, 1024, IPC_CREAT | 0666);

    if (shmid == -1) {
        perror("Shared memory creation failed");
        return 1;
    }

    shared_memory = (char *)shmat(shmid, NULL, 0);

    if (shared_memory == (char *)-1) {
        perror("Shared memory attachment failed");
        shmctl(shmid, IPC_RMID, NULL);
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        shmdt(shared_memory);
        shmctl(shmid, IPC_RMID, NULL);
        return 1;
    }
    else if (pid == 0) {
        printf("Child reads: %s\n", shared_memory);
    }
    else {
        strcpy(shared_memory, "Hello from parent using shared memory!");
        wait(NULL);
    }

    shmdt(shared_memory);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
