#include <stdio.h>

int get_crypto_version(void) {
    return 1;
}

unsigned long encrypt_tx(unsigned long amount, unsigned long key) {
    return (amount ^ key) + (get_crypto_version() * 1000UL);
}
