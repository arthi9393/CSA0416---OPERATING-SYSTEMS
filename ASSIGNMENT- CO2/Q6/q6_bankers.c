
#include <stdio.h>

#define P 5
#define R 3

int main() {
    int allocation[P][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int maximum[P][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int available[R] = {3, 3, 2};
    int need[P][R];
    int finish[P] = {0};
    int safeSequence[P];

    int i, j, count = 0;

    for (i = 0; i < P; i++) {
        for (j = 0; j < R; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    printf("Need Matrix:\n");
    for (i = 0; i < P; i++) {
        for (j = 0; j < R; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    while (count < P) {
        int found = 0;

        for (i = 0; i < P; i++) {
            if (finish[i] == 0) {
                int possible = 1;

                for (j = 0; j < R; j++) {
                    if (need[i][j] > available[j]) {
                        possible = 0;
                        break;
                    }
                }

                if (possible) {
                    for (j = 0; j < R; j++) {
                        available[j] += allocation[i][j];
                    }

                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found) {
            break;
        }
    }

    if (count == P) {
        printf("\nSystem is in a SAFE state.\n");
        printf("Safe Sequence: ");
        for (i = 0; i < P; i++) {
            printf("P%d", safeSequence[i]);
            if (i < P - 1) printf(" -> ");
        }
        printf("\n");
    } else {
        printf("\nSystem is in an UNSAFE state.\n");
    }

    return 0;
}
