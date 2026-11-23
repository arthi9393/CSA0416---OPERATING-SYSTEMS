/* Q34: Sequential file allocation (CO4)
   Records stored contiguously; a record is reached by reading all previous ones. */
#include <stdio.h>
#include <string.h>

#define DISK 50

int main(void) {
    int used[DISK] = {0}, nfiles, i, j;
    char name[20][30];
    int start[20], len[20];

    printf("Enter number of files: "); scanf("%d", &nfiles);
    for (i = 0; i < nfiles; i++) {
        printf("\nFile %d name: ", i + 1); scanf("%29s", name[i]);
        printf("Starting block (0-%d): ", DISK - 1); scanf("%d", &start[i]);
        printf("Length (blocks): "); scanf("%d", &len[i]);

        int ok = (start[i] >= 0 && start[i] + len[i] <= DISK);
        for (j = start[i]; ok && j < start[i] + len[i]; j++) if (used[j]) ok = 0;
        if (!ok) { printf("Cannot allocate: blocks out of range or already in use.\n"); len[i] = 0; continue; }
        for (j = start[i]; j < start[i] + len[i]; j++) used[j] = 1;
        printf("File %s allocated: ", name[i]);
        for (j = start[i]; j < start[i] + len[i]; j++) printf("%d ", j);
        printf("\n");
    }

    printf("\nDirectory\nFile\tStart\tLength\n");
    for (i = 0; i < nfiles; i++) if (len[i]) printf("%s\t%d\t%d\n", name[i], start[i], len[i]);

    char q[30]; int rec;
    printf("\nEnter file name to access: "); scanf("%29s", q);
    for (i = 0; i < nfiles; i++) if (len[i] && strcmp(q, name[i]) == 0) {
        printf("Enter record number (1-%d): ", len[i]); scanf("%d", &rec);
        if (rec < 1 || rec > len[i]) { printf("Invalid record.\n"); return 0; }
        printf("Sequential access reads blocks: ");
        for (j = 0; j < rec; j++) printf("%d ", start[i] + j);
        printf("\nRecord %d is at block %d (%d block(s) read)\n", rec, start[i] + rec - 1, rec);
        return 0;
    }
    printf("File not found.\n");
    return 0;
}
