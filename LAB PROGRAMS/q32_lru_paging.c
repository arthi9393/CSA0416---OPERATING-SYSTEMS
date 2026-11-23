/* Q32: LRU page replacement (CO3) */
#include <stdio.h>

int main(void) {
    int nf, n, i, j, ref[100], frame[20], last[20], faults = 0;
    printf("Enter number of frames: "); scanf("%d", &nf);
    printf("Enter length of reference string: "); scanf("%d", &n);
    printf("Enter reference string: ");
    for (i = 0; i < n; i++) scanf("%d", &ref[i]);
    for (i = 0; i < nf; i++) { frame[i] = -1; last[i] = -1; }

    printf("\nPage\tFrames\t\tStatus\n");
    for (i = 0; i < n; i++) {
        int hit = 0, pos = -1;
        for (j = 0; j < nf; j++) if (frame[j] == ref[i]) { hit = 1; pos = j; break; }
        if (hit) last[pos] = i;
        else {
            for (j = 0; j < nf; j++) if (frame[j] == -1) { pos = j; break; }   /* empty frame first */
            if (pos == -1) {                                                   /* else least recently used */
                pos = 0;
                for (j = 1; j < nf; j++) if (last[j] < last[pos]) pos = j;
            }
            frame[pos] = ref[i]; last[pos] = i; faults++;
        }
        printf("%d\t", ref[i]);
        for (j = 0; j < nf; j++) { if (frame[j] == -1) printf("- "); else printf("%d ", frame[j]); }
        printf("\t%s\n", hit ? "Hit" : "Fault");
    }
    printf("\nTotal page faults = %d\nTotal hits = %d\nHit ratio = %.2f\n", faults, n - faults, (float)(n - faults) / n);
    return 0;
}
