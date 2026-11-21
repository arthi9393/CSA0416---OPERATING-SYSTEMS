#include <stdio.h>
#include <stdlib.h>

extern int get_crypto_version(void);
extern unsigned long encrypt_tx(unsigned long amount, unsigned long key);

int main(int argc, char *argv[]) {
    unsigned long cipher = encrypt_tx(50000UL, 0xABCD1234UL);
    printf("Crypto Lib v%d | Encrypted TX: 0x%lx\n", get_crypto_version(), cipher);

    if (argc > 1 && argv[1][0] == 'm') {
        FILE *f = fopen("/proc/self/maps", "r");
        char line[256];
        int count = 0;
        printf("--- /proc/self/maps (Top 10 mappings) ---\n");
        while (f && fgets(line, sizeof(line), f) && count++ < 10) {
            printf("%s", line);
        }
        if (f) fclose(f);
    }
    return 0;
}
