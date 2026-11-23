/* Q36: Linked file allocation (CO4)
   Blocks may be scattered; the directory holds pointers to the first and
   last blocks and each block holds a pointer to the next block. */
#include <stdio.h>
#include <string.h>

#define DISK 50

int main(void) {
    int next[DISK], used[DISK] = {0}, nfiles, i, j;
    char name[20][30];
    int first[20], last[20], cnt[20];

    for (i = 0; i < DISK; i++) next[i] = -1;
    printf("Enter number of files: "); scanf("%d", &nfiles);
    for (i = 0; i < nfiles; i++) {
        cnt[i] = 0; first[i] = last[i] = -1;
        printf("\nFile %d name: ", i + 1); scanf("%29s", name[i]);
        int n; printf("Number of blocks: "); scanf("%d", &n);
        printf("Enter %d block numbers (in order): ", n);
        for (j = 0; j < n; j++) {
            int b; scanf("%d", &b);
            if (b < 0 || b >= DISK || used[b]) { printf("  block %d unavailable, skipped\n", b); continue; }
            used[b] = 1;
            if (first[i] == -1) first[i] = b; else next[last[i]] = b;
            last[i] = b; cnt[i]++;
        }
    }

    printf("\nDirectory\nFile\tFirst\tLast\tBlocks\n");
    for (i = 0; i < nfiles; i++) printf("%s\t%d\t%d\t%d\n", name[i], first[i], last[i], cnt[i]);

    printf("\nBlock chains\n");
    for (i = 0; i < nfiles; i++) {
        printf("%s: ", name[i]);
        for (int b = first[i]; b != -1; b = next[b]) printf("[%d]%s", b, next[b] == -1 ? " -> NULL" : " -> ");
        printf("\n");
    }

    char q[30]; int k;
    printf("\nFile to access: "); scanf("%29s", q);
    for (i = 0; i < nfiles; i++) if (strcmp(q, name[i]) == 0) {
        printf("Enter logical block number (1-%d): ", cnt[i]); scanf("%d", &k);
        if (k < 1 || k > cnt[i]) { printf("Invalid block.\n"); return 0; }
        int b = first[i];
        printf("Traversal: %d", b);
        for (j = 1; j < k; j++) { b = next[b]; printf(" -> %d", b); }
        printf("\nLogical block %d is physical block %d\n", k, b);
        return 0;
    }
    printf("File not found.\n");
    return 0;
}
