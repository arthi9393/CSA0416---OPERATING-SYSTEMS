
#include <stdio.h>

int main() {
    int n, i, time = 0, done = 0, best;
    int at[20], bt[20], rem[20], pr[20];
    int ct[20] = {0}, wt[20], tat[20];
    float awt = 0, atat = 0;

    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("Arrival, burst, priority: ");
        scanf("%d%d%d", &at[i], &bt[i], &pr[i]);
        rem[i] = bt[i];
    }

    while (done < n) {
        best = -1;
        for (i = 0; i < n; i++)
            if (at[i] <= time && rem[i] > 0 &&
                (best == -1 || pr[i] < pr[best]))
                best = i;

        if (best == -1) {
            time++;
            continue;
        }

        rem[best]--;
        time++;

        if (rem[best] == 0) {
            ct[best] = time;
            done++;
        }
    }

    for (i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        awt += wt[i];
        atat += tat[i];
        printf("P%d WT=%d TAT=%d\n", i+1, wt[i], tat[i]);
    }

    printf("Average WT = %.2f\n", awt/n);
    printf("Average TAT = %.2f\n", atat/n);
    return 0;
}
