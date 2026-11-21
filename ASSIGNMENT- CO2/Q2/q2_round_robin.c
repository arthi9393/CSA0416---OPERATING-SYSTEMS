
#include <stdio.h>

int main() {
    int n, tq, i, time = 0, completed = 0;
    int at[20], bt[20], rt[20], ct[20];
    int wt[20], tat[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    if (tq <= 0) {
        printf("Time quantum must be positive.\n");
        return 1;
    }

    int queue[1000], front = 0, rear = 0;
    int inQueue[20] = {0};

    printf("\nExecution order:\n");

    // Start at the earliest arrival time
    for (i = 0; i < n; i++) {
        if (at[i] == 0) {
            queue[rear++] = i;
            inQueue[i] = 1;
        }
    }

    while (completed < n) {
        if (front == rear) {
            time++;
            for (i = 0; i < n; i++) {
                if (!inQueue[i] && rt[i] > 0 && at[i] <= time) {
                    queue[rear++] = i;
                    inQueue[i] = 1;
                }
            }
            continue;
        }

        int p = queue[front++];

        printf("P%d ", p + 1);

        int run = (rt[p] < tq) ? rt[p] : tq;
        rt[p] -= run;
        time += run;

        // Add newly arrived processes
        for (i = 0; i < n; i++) {
            if (!inQueue[i] && rt[i] > 0 && at[i] <= time) {
                queue[rear++] = i;
                inQueue[i] = 1;
            }
        }

        if (rt[p] > 0) {
            queue[rear++] = p;
        } else {
            completed++;
            ct[p] = time;
            tat[p] = ct[p] - at[p];
            wt[p] = tat[p] - bt[p];
        }
    }

    float totalWT = 0, totalTAT = 0;

    printf("\n\nProcess\tAT\tBT\tCT\tWT\tTAT\n");

    for (i = 0; i < n; i++) {
        totalWT += wt[i];
        totalTAT += tat[i];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", totalWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", totalTAT / n);

    return 0;
}
