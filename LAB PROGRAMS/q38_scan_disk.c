/* Q38: SCAN (elevator) disk scheduling (CO4) */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n, i, j, head, size, dir, req[100], total = 0, t;
    printf("Enter number of requests: "); scanf("%d", &n);
    printf("Enter request queue: ");
    for (i = 0; i < n; i++) scanf("%d", &req[i]);
    printf("Enter initial head position: "); scanf("%d", &head);
    printf("Enter disk size (cylinders 0 to size-1): "); scanf("%d", &size);
    printf("Direction (1 = towards higher, 0 = towards lower): "); scanf("%d", &dir);

    for (i = 0; i < n - 1; i++)                      /* sort requests */
        for (j = 0; j < n - i - 1; j++)
            if (req[j] > req[j + 1]) { t = req[j]; req[j] = req[j + 1]; req[j + 1] = t; }

    int split = 0;
    while (split < n && req[split] < head) split++;  /* req[0..split-1] below head */

    int cur = head;
    printf("\nSeek sequence: %d", head);
    if (dir == 1) {
        for (i = split; i < n; i++) { total += abs(req[i] - cur); cur = req[i]; printf(" -> %d", cur); }
        if (split > 0) {
            total += abs((size - 1) - cur); cur = size - 1; printf(" -> %d", cur);   /* go to the end */
            for (i = split - 1; i >= 0; i--) { total += abs(req[i] - cur); cur = req[i]; printf(" -> %d", cur); }
        }
    } else {
        for (i = split - 1; i >= 0; i--) { total += abs(req[i] - cur); cur = req[i]; printf(" -> %d", cur); }
        if (split < n) {
            total += cur; cur = 0; printf(" -> 0");                                   /* go to the start */
            for (i = split; i < n; i++) { total += abs(req[i] - cur); cur = req[i]; printf(" -> %d", cur); }
        }
    }
    printf("\n\nTotal head movement = %d cylinders\nAverage seek length = %.2f\n", total, (float)total / n);
    return 0;
}
