/* Q37: FCFS disk scheduling (CO4) */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n, i, head, req[100], total = 0;
    printf("Enter number of requests: "); scanf("%d", &n);
    printf("Enter request queue: ");
    for (i = 0; i < n; i++) scanf("%d", &req[i]);
    printf("Enter initial head position: "); scanf("%d", &head);

    printf("\nSeek sequence: %d", head);
    int cur = head;
    for (i = 0; i < n; i++) {
        int d = abs(req[i] - cur);
        total += d;
        printf(" -> %d", req[i]);
        cur = req[i];
    }
    printf("\n\nTotal head movement = %d cylinders\nAverage seek length = %.2f\n", total, (float)total / n);
    return 0;
}
