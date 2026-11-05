
#include <stdio.h>

int main() {
    int n, i, time = 0, completed = 0;
    int at[20], bt[20], pr[20], ct[20];
    int wt[20], tat[20], done[20] = {0};

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter arrival time, burst time and priority for P%d: ", i + 1);
        scanf("%d %d %d", &at[i], &bt[i], &pr[i]);
    }

    float totalWT = 0, totalTAT = 0;

    printf("\nProcess\tAT\tBT\tPriority\tCT\tWT\tTAT\n");

    while (completed < n) {
        int highest = -1;

        for (i = 0; i < n; i++) {
            if (!done[i] && at[i] <= time) {
                if (highest == -1 || pr[i] < pr[highest])
                    highest = i;
            }
        }

        if (highest == -1) {
            time++;
            continue;
        }

        time += bt[highest];

        ct[highest] = time;
        tat[highest] = ct[highest] - at[highest];
        wt[highest] = tat[highest] - bt[highest];

        totalWT += wt[highest];
        totalTAT += tat[highest];

        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               highest + 1, at[highest], bt[highest],
               pr[highest], ct[highest], wt[highest], tat[highest]);

        done[highest] = 1;
        completed++;
    }

    printf("\nAverage Waiting Time = %.2f", totalWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", totalTAT / n);

    return 0;
}
