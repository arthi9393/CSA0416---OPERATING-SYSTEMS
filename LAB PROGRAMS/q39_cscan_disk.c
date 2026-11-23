/* Q39: C-SCAN disk scheduling (CO4) */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n, i, j, head, size, req[100], total = 0, t;
    printf("Enter number of requests: "); scanf("%d", &n);
    printf("Enter request queue: ");
    for (i = 0; i < n; i++) scanf("%d", &req[i]);
    printf("Enter initial head position: "); scanf("%d", &head);
    printf("Enter disk size (cylinders 0 to size-1): "); scanf("%d", &size);

    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (req[j] > req[j + 1]) { t = req[j]; req[j] = req[j + 1]; req[j + 1] = t; }

    int split = 0;
    while (split < n && req[split] < head) split++;

    /* The head services requests while moving towards higher cylinders,
       jumps from the last cylinder to cylinder 0, then continues upward. */
    int cur = head;
    printf("\nSeek sequence: %d", head);
    for (i = split; i < n; i++) { total += abs(req[i] - cur); cur = req[i]; printf(" -> %d", cur); }
    if (split > 0) {
        total += (size - 1) - cur; cur = size - 1; printf(" -> %d", cur);
        total += size - 1; cur = 0; printf(" -> 0");              /* return jump counted as head movement */
        for (i = 0; i < split; i++) { total += abs(req[i] - cur); cur = req[i]; printf(" -> %d", cur); }
    }
    printf("\n\nTotal head movement = %d cylinders (including return jump)\nAverage seek length = %.2f\n", total, (float)total / n);
    return 0;
}
