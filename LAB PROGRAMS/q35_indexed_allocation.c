/* Q35: Indexed file allocation (CO4)
   All pointers of a file are brought together in an index block;
   the i-th entry points to the i-th block of the file. */
#include <stdio.h>
#include <string.h>

#define DISK 50

int main(void) {
    int used[DISK] = {0}, nfiles, i, j;
    char name[20][30];
    int index[20], cnt[20], blocks[20][DISK];

    printf("Enter number of files: "); scanf("%d", &nfiles);
    for (i = 0; i < nfiles; i++) {
        cnt[i] = 0;
        printf("\nFile %d name: ", i + 1); scanf("%29s", name[i]);
        printf("Index block (0-%d): ", DISK - 1); scanf("%d", &index[i]);
        if (index[i] < 0 || index[i] >= DISK || used[index[i]]) { printf("Index block unavailable.\n"); continue; }
        used[index[i]] = 1;
        int n; printf("Number of data blocks: "); scanf("%d", &n);
        printf("Enter the %d block numbers: ", n);
        for (j = 0; j < n; j++) {
            int b; scanf("%d", &b);
            if (b < 0 || b >= DISK || used[b]) { printf("  block %d unavailable, skipped\n", b); continue; }
            used[b] = 1; blocks[i][cnt[i]++] = b;
        }
    }

    printf("\nDirectory\nFile\tIndex block\n");
    for (i = 0; i < nfiles; i++) printf("%s\t%d\n", name[i], index[i]);

    printf("\nIndex block contents\n");
    for (i = 0; i < nfiles; i++) {
        printf("%s (index block %d):\n", name[i], index[i]);
        for (j = 0; j < cnt[i]; j++) printf("  entry %d -> block %d\n", j, blocks[i][j]);
    }

    char q[30]; int k;
    printf("\nFile to access: "); scanf("%29s", q);
    for (i = 0; i < nfiles; i++) if (strcmp(q, name[i]) == 0) {
        printf("Enter logical block number (0-%d): ", cnt[i] - 1); scanf("%d", &k);
        if (k >= 0 && k < cnt[i]) printf("Direct access via index: logical block %d -> physical block %d\n", k, blocks[i][k]);
        else printf("Invalid block.\n");
        return 0;
    }
    printf("File not found.\n");
    return 0;
}
