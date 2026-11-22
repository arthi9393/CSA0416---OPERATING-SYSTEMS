/* Simple static SSTF workload simulation scaffold.
 * Compile: gcc -std=c11 -Wall -Wextra -O2 sstf_batch.c -o sstf_batch
 * This computes service movement for a batch; waiting-time modelling requires
 * arrival times and an explicit seek/service-time model.
 */
#include <stdio.h>
#include <stdlib.h>
#define NREQ 10000
#define CYLINDERS 200
int main(void) {
    int *r = malloc(NREQ * sizeof *r);
    unsigned char *done = calloc(NREQ, sizeof *done);
    if (!r || !done) { perror("allocation"); free(r); free(done); return 1; }
    srand(42);
    for (int i = 0; i < NREQ; i++) r[i] = rand() % CYLINDERS;
    int head = 53;
    long long movement = 0;
    for (int k = 0; k < NREQ; k++) {
        int best = -1, dist_best = CYLINDERS + 1;
        for (int i = 0; i < NREQ; i++) if (!done[i]) {
            int d = abs(r[i] - head);
            if (d < dist_best) { dist_best = d; best = i; }
        }
        done[best] = 1;
        movement += dist_best;
        head = r[best];
    }
    printf("Requests: %d\\nTotal SSTF movement: %lld cylinders\\n", NREQ, movement);
    free(r); free(done);
    return 0;
}
