
#include <stdio.h>

int main() {
    int n, i, bt[20], wt[20], tat[20];
    float awt = 0, atat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Burst time P%d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    wt[0] = 0;
    for (i = 1; i < n; i++)
        wt[i] = wt[i-1] + bt[i-1];

    for (i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
        awt += wt[i];
        atat += tat[i];
    }

    printf("P\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\n",
               i+1, bt[i], wt[i], tat[i]);

    printf("Average WT = %.2f\n", awt/n);
    printf("Average TAT = %.2f\n", atat/n);
    return 0;
}
