
#include <stdio.h>

int main() {
    int n, i, time = 0, completed = 0;
    int at[20], bt[20], rt[20], ct[20];
    int wt[20], tat[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    float totalWT = 0, totalTAT = 0;

    printf("\nGantt Chart:\n");

    while (completed < n) {
        int shortest = -1;

        for (i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0) {
                if (shortest == -1 || rt[i] < rt[shortest])
                    shortest = i;
            }
        }

        if (shortest == -1) {
            time++;
            continue;
        }

        printf("| P%d ", shortest + 1);
        rt[shortest]--;
        time++;

        if (rt[shortest] == 0) {
            completed++;
            ct[shortest] = time;
            tat[shortest] = ct[shortest] - at[shortest];
            wt[shortest] = tat[shortest] - bt[shortest];

            totalWT += wt[shortest];
            totalTAT += tat[shortest];
        }
    }

    printf("|\n\nProcess\tAT\tBT\tCT\tWT\tTAT\n");

    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", totalWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", totalTAT / n);

    return 0;
}
