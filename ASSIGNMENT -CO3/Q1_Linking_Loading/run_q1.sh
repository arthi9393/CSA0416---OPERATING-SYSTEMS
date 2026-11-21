#!/bin/bash
set -e
gcc -O2 -static bank_app.c libcrypto_bank.c -o bank_static
gcc -fPIC -shared libcrypto_bank.c -o libcrypto_bank.so
gcc -O2 bank_app.c -L. -lcrypto_bank -Wl,-rpath,. -o bank_dynamic
gcc -O2 bank_dlopen.c -ldl -o bank_dlopen

ls -lh bank_static bank_dynamic libcrypto_bank.so bank_dlopen
ldd bank_dynamic
./bank_static
./bank_dynamic m
./bank_dlopen
