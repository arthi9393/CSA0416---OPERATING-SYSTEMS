#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <time.h>

static double now_us(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1e6 + ts.tv_nsec / 1e3;
}

static long minor_faults(void) {
    struct rusage ru;
    getrusage(RUSAGE_SELF, &ru);
    return ru.ru_minflt;
}

void test_rt_loop(int lock_mem) {
    const size_t RT_SIZE = 120UL * 1024 * 1024;
    char *buf = mmap(NULL, RT_SIZE, PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (buf == MAP_FAILED) { perror("mmap"); return; }

    if (lock_mem) {
        if (mlockall(MCL_CURRENT | MCL_FUTURE) != 0) {
            perror("mlockall");
        }
        memset(buf, 0, RT_SIZE);
    }

    long f_start = minor_faults();
    double max_lat = 0.0, sum_lat = 0.0;
    const int ITERS = 5000;

    for (int i = 0; i < ITERS; i++) {
        double t0 = now_us();
        size_t idx = ((size_t)i * 4096) % RT_SIZE;
        buf[idx] = (char)(i & 0xFF);
        double dt = now_us() - t0;
        if (dt > max_lat) max_lat = dt;
        sum_lat += dt;
    }

    long f_end = minor_faults();
    printf("Mode: %-8s | Avg Latency: %6.2f us | Worst-Case Latency: %8.2f us | Loop Faults: %ld\n",
           lock_mem ? "LOCKED" : "UNLOCKED", sum_lat / ITERS, max_lat, f_end - f_start);

    if (lock_mem) munlockall();
    munmap(buf, RT_SIZE);
}

int main(void) {
    printf("=== Q7: Smart Factory Real-Time Control Loop Latency ===\n");
    test_rt_loop(0);
    test_rt_loop(1);
    return 0;
}
