/* Q21: Worst Fit algorithm of memory management (CO3) */
#include <stdio.h>

int main(void) {
    int nb, np, i, j;
    int block[50], alloc[50], proc[50];

    printf("Enter number of memory blocks: ");
    scanf("%d", &nb);
    printf("Enter size of each block: ");
    for (i = 0; i < nb; i++) scanf("%d", &block[i]);
    printf("Enter number of processes: ");
    scanf("%d", &np);
    printf("Enter size of each process: ");
    for (i = 0; i < np; i++) scanf("%d", &proc[i]);

    for (i = 0; i < np; i++) {
        int pick = -1;
        for (j = 0; j < nb; j++)
            if (block[j] >= proc[i] && (pick == -1 || block[j] > block[pick])) pick = j;
        alloc[i] = pick;
        if (pick != -1) block[pick] -= proc[i];   /* remaining space in block */
    }

    printf("\n%-8s %-10s %-8s %-12s\n", "Process", "Size", "Block", "Remaining");
    for (i = 0; i < np; i++) {
        printf("P%-7d %-10d ", i + 1, proc[i]);
        if (alloc[i] != -1) printf("%-8d %-12d\n", alloc[i] + 1, block[alloc[i]]);
        else printf("%-8s %-12s\n", "Not allocated", "-");
    }
    return 0;
}
