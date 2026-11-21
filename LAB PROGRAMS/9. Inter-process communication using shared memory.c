
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main() {
    int id = shmget(IPC_PRIVATE, 1024, IPC_CREAT | 0600);
    char *data;

    if (id < 0) {
        perror("shmget");
        return 1;
    }

    data = (char *)shmat(id, NULL, 0);
    if (data == (char *)-1) {
        perror("shmat");
        shmctl(id, IPC_RMID, NULL);
        return 1;
    }

    strcpy(data, "Hello from shared memory!");

    if (fork() == 0) {
        char *child = (char *)shmat(id, NULL, 0);
        if (child != (char *)-1) {
            printf("Child reads: %s\n", child);
            shmdt(child);
        }
        _exit(0);
    }

    wait(NULL);
    shmdt(data);
    shmctl(id, IPC_RMID, NULL);
    return 0;
}
