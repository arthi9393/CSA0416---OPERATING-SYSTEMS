
#include <stdio.h>

int main() {
    int n, i, completed = 0, time = 0;
    int at[20], bt[20], wt[20], tat[20], ct[20];
    int done[20] = {0};

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
    }

    float totalWT = 0, totalTAT = 0;

    printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");

    while (completed < n) {
        int shortest = -1;

        for (i = 0; i < n; i++) {
            if (!done[i] && at[i] <= time) {
                if (shortest == -1 || bt[i] < bt[shortest])
                    shortest = i;
            }
        }

        if (shortest == -1) {
            time++;
            continue;
        }

        time += bt[shortest];
        ct[shortest] = time;
        tat[shortest] = ct[shortest] - at[shortest];
        wt[shortest] = tat[shortest] - bt[shortest];

        totalWT += wt[shortest];
        totalTAT += tat[shortest];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               shortest + 1, at[shortest], bt[shortest],
               ct[shortest], wt[shortest], tat[shortest]);

        done[shortest] = 1;
        completed++;
    }

    printf("\nAverage Waiting Time = %.2f", totalWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", totalTAT / n);

    return 0;
}
