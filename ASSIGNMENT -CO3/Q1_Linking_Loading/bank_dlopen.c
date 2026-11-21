#include <stdio.h>
#include <dlfcn.h>

int main(void) {
    void *handle = dlopen("./libcrypto_bank.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "dlopen error handled gracefully: %s\n", dlerror());
        return 1;
    }
    unsigned long (*enc_fn)(unsigned long, unsigned long) = dlsym(handle, "encrypt_tx");
    char *err = dlerror();
    if (err != NULL) {
        fprintf(stderr, "dlsym error: %s\n", err);
        dlclose(handle);
        return 1;
    }
    printf("Runtime dlopen() Encrypted TX: 0x%lx\n", enc_fn(50000UL, 0xABCD1234UL));
    dlclose(handle);
    return 0;
}
