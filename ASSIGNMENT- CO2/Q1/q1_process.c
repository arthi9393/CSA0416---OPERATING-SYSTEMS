

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    printf("Parent process started.\n");

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0) {
        printf("\nChild process is running.\n");
        printf("Child Process ID: %d\n", getpid());
        printf("Parent Process ID: %d\n", getppid());
    }
    else {
        wait(NULL);
        printf("\nParent process is running.\n");
        printf("Parent Process ID: %d\n", getpid());
        printf("Child Process ID: %d\n", pid);
    }

    return 0;
}
