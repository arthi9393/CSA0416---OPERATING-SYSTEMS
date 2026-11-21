#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <time.h>

static long get_minor_faults(void) {
    struct rusage ru;
    getrusage(RUSAGE_SELF, &ru);
    return ru.ru_minflt;
}

static double now_sec(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec * 1e-9;
}

int main(void) {
    const size_t SIZE = 256UL * 1024 * 1024;
    const size_t PAGE = 4096;
    char *buf = malloc(SIZE);
    if (!buf) return 1;

    long f0 = get_minor_faults();
    double t0 = now_sec();
    for (size_t i = 0; i < SIZE; i += PAGE) buf[i] = 1;
    double t1 = now_sec();
    long f1 = get_minor_faults();
    printf("Sequential Touch (256 MB): Time = %.4f s | Minor Faults = %ld\n", t1 - t0, f1 - f0);

    pid_t pid = fork();
    if (pid == 0) {
        long cf0 = get_minor_faults();
        volatile char sum = 0;
        for (size_t i = 0; i < SIZE; i += PAGE) sum += buf[i];
        long cf1 = get_minor_faults();

        for (size_t i = 0; i < SIZE / 2; i += PAGE) buf[i] = 2;
        long cf2 = get_minor_faults();

        printf("Child after fork() read-only scan: %ld new faults\n", cf1 - cf0);
        printf("Child after writing 128 MB (COW):  %ld new faults\n", cf2 - cf1);
        _exit(0);
    } else {
        wait(NULL);
    }
    free(buf);
    return 0;
}
