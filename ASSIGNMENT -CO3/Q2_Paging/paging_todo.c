#include <stdio.h>
#include <stdlib.h>

#ifndef PAGE_SIZE
#define PAGE_SIZE 1024
#endif
#define PAGES 8

int page_table[PAGES] = {5, 2, -1, 7, 0, -1, 3, -1};

void run_experiments(void) {
    printf("\n--- Experimental Investigation ---\n");
    int page_sizes[] = {1024, 4096, 2097152};
    srand(42);
    int proc_sizes[100];
    for (int i = 0; i < 100; i++) proc_sizes[i] = (rand() % 500 + 1) * 1024;

    for (int s = 0; s < 3; s++) {
        long long total_frag = 0;
        int ps = page_sizes[s];
        for (int i = 0; i < 100; i++) {
            int rem = proc_sizes[i] % ps;
            total_frag += (rem == 0) ? 0 : (ps - rem);
        }
        printf("Page Size %7d B -> Total Internal Fragmentation (100 procs): %lld KB\n",
               ps, total_frag / 1024);
    }

    double hits[] = {0.80, 0.95, 0.99};
    double t_tlb = 10.0, t_mem = 100.0;
    for (int i = 0; i < 3; i++) {
        double emat = hits[i] * (t_tlb + t_mem) + (1.0 - hits[i]) * (t_tlb + 2.0 * t_mem);
        printf("TLB Hit Ratio %.0f%% -> EMAT = %.2f ns\n", hits[i] * 100.0, emat);
    }
}

int main(void) {
    printf("=== Address Translation (PAGE_SIZE = %d) ===\n", PAGE_SIZE);
    unsigned logical[] = {0, 1500, 3100, 6200, 9000, 2049};
    for (int i = 0; i < 6; i++) {
        unsigned a = logical[i];
        unsigned p = a / PAGE_SIZE;
        unsigned d = a % PAGE_SIZE;
        if (p >= PAGES) {
            printf("%u -> page %u offset %u : invalid address\n", a, p, d);
        } else if (page_table[p] == -1) {
            printf("%u -> page %u offset %u : page fault\n", a, p, d);
        } else {
            unsigned phys = (unsigned)page_table[p] * PAGE_SIZE + d;
            printf("%u -> page %u offset %u : physical %u\n", a, p, d, phys);
        }
    }
    run_experiments();
    return 0;
}
