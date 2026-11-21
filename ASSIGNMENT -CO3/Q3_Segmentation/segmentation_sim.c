#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *name;
    unsigned base;
    unsigned limit;
} Segment;

int main(void) {
    Segment seg_table[4] = {
        {"Code",  1000, 500},
        {"Data",  3000, 800},
        {"Stack", 5000, 400},
        {"Heap",  7000, 600}
    };

    unsigned tests[8][2] = {
        {0, 120}, {0, 500}, {1, 799}, {1, 850},
        {2, 0},   {2, 410}, {3, 250}, {4, 10}
    };

    printf("=== Q3: Segment Address Translation ===\n");
    for (int i = 0; i < 8; i++) {
        unsigned s = tests[i][0];
        unsigned off = tests[i][1];
        if (s >= 4) {
            printf("(%u, %u) -> TRAP: Invalid Segment Number\n", s, off);
        } else if (off >= seg_table[s].limit) {
            printf("(%u [%s], %u) -> TRAP: Segmentation Fault (offset >= limit %u)\n",
                   s, seg_table[s].name, off, seg_table[s].limit);
        } else {
            printf("(%u [%s], %u) -> Physical Address: %u\n",
                   s, seg_table[s].name, off, seg_table[s].base + off);
        }
    }
    return 0;
}
