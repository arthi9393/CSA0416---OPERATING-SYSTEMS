#include <stdio.h>
#include <math.h>

int main(void) {
    int disks = 6;
    double cap_tb = 4.0;
    double p_fail = 0.02;

    printf("=== Q6: RAID Capacity & Reliability (6 x 4 TB Disks) ===\n");
    printf("RAID 0  Usable: %.1f TB\n", disks * cap_tb);
    printf("RAID 1  Usable: %.1f TB\n", (disks / 2.0) * cap_tb);
    printf("RAID 5  Usable: %.1f TB\n", (disks - 1) * cap_tb);
    printf("RAID 6  Usable: %.1f TB\n", (disks - 2) * cap_tb);
    printf("RAID 10 Usable: %.1f TB\n", (disks / 2.0) * cap_tb);

    double p_raid1_pair = pow(p_fail, 2);
    double p_raid1_3pairs = 1.0 - pow(1.0 - p_raid1_pair, 3);
    double p_raid5 = 1.0 - pow(1.0 - p_fail, 6) - 6.0 * p_fail * pow(1.0 - p_fail, 5);

    printf("\n=== Probability of Data Loss (p = %.2f) ===\n", p_fail);
    printf("RAID 1 (single pair):  %.6f (%.4f%%)\n", p_raid1_pair, p_raid1_pair * 100.0);
    printf("RAID 10 (3 pairs):     %.6f (%.4f%%)\n", p_raid1_3pairs, p_raid1_3pairs * 100.0);
    printf("RAID 5 (6-disk array): %.6f (%.4f%%)\n", p_raid5, p_raid5 * 100.0);
    return 0;
}
