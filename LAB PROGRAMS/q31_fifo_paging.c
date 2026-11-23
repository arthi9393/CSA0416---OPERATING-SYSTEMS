/* Q31: FIFO page replacement (CO3) */
#include <stdio.h>

int main(void) {
    int nf, n, i, j, ref[100], frame[20], next = 0, faults = 0;
    printf("Enter number of frames: "); scanf("%d", &nf);
    printf("Enter length of reference string: "); scanf("%d", &n);
    printf("Enter reference string: ");
    for (i = 0; i < n; i++) scanf("%d", &ref[i]);
    for (i = 0; i < nf; i++) frame[i] = -1;

    printf("\nPage\tFrames\t\tStatus\n");
    for (i = 0; i < n; i++) {
        int hit = 0;
        for (j = 0; j < nf; j++) if (frame[j] == ref[i]) { hit = 1; break; }
        if (!hit) { frame[next] = ref[i]; next = (next + 1) % nf; faults++; }
        printf("%d\t", ref[i]);
        for (j = 0; j < nf; j++) { if (frame[j] == -1) printf("- "); else printf("%d ", frame[j]); }
        printf("\t%s\n", hit ? "Hit" : "Fault");
    }
    printf("\nTotal page faults = %d\nTotal hits = %d\nHit ratio = %.2f\n", faults, n - faults, (float)(n - faults) / n);
    return 0;
}
