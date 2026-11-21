
#include <stdio.h>

int main() {
    int n, i, q, time = 0, done;
    int bt[20], rem[20], wt[20], tat[20];
    float awt = 0, atat = 0;

    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
        rem[i] = bt[i];
    }
    printf("Enter time quantum: ");
    scanf("%d", &q);

    if (q <= 0) {
        printf("Invalid quantum\n");
        return 1;
    }

    do {
        done = 1;
        for (i = 0; i < n; i++) {
            if (rem[i] > 0) {
                done = 0;
                if (rem[i] > q) {
                    time += q;
                    rem[i] -= q;
                } else {
                    time += rem[i];
                    wt[i] = time - bt[i];
                    rem[i] = 0;
                }
            }
        }
    } while (!done);

    for (i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
        awt += wt[i];
        atat += tat[i];
        printf("P%d WT=%d TAT=%d\n", i+1, wt[i], tat[i]);
    }

    printf("Average WT = %.2f\n", awt/n);
    printf("Average TAT = %.2f\n", atat/n);
    return 0;
}
