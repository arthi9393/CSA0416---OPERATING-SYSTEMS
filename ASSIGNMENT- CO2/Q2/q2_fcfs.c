
#include <stdio.h>

int main() {
    int n, i;
    int at[20], bt[20], wt[20], tat[20];
    int ct[20], p[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        p[i] = i + 1;
        printf("Enter arrival time and burst time for P%d: ", p[i]);
        scanf("%d %d", &at[i], &bt[i]);
    }

    // Sort processes by arrival time
    for (i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (at[i] > at[j]) {
                int temp;

                temp = at[i]; at[i] = at[j]; at[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                temp = p[i]; p[i] = p[j]; p[j] = temp;
            }
        }
    }

    int time = 0;
    float totalWT = 0, totalTAT = 0;

    printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");

    for (i = 0; i < n; i++) {
        if (time < at[i])
            time = at[i];

        time += bt[i];
        ct[i] = time;
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        totalWT += wt[i];
        totalTAT += tat[i];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i], at[i], bt[i], ct[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", totalWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", totalTAT / n);

    return 0;
}
