
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int p = fork();
    if (p == 0)
        printf("Child PID=%d, Parent PID=%d\n", getpid(), getppid());
    else {
        printf("Parent PID=%d\n", getpid());
        wait(NULL);
    }
    return 0;
}
