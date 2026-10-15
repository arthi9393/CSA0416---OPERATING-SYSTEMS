
#include <stdio.h>

int main() {
    int n, i, j, bt[20], p[20], t, wt[20], tat[20];
    float awt = 0, atat = 0;

    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
        p[i] = i + 1;
    }

    for (i = 0; i < n-1; i++)
        for (j = i+1; j < n; j++)
            if (bt[i] > bt[j]) {
                t=bt[i]; bt[i]=bt[j]; bt[j]=t;
                t=p[i]; p[i]=p[j]; p[j]=t;
            }

    wt[0] = 0;
    for (i = 1; i < n; i++)
        wt[i] = wt[i-1] + bt[i-1];

    for (i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
        awt += wt[i];
        atat += tat[i];
        printf("P%d WT=%d TAT=%d\n", p[i], wt[i], tat[i]);
    }

    printf("Average WT = %.2f\n", awt/n);
    printf("Average TAT = %.2f\n", atat/n);
    return 0;
}
