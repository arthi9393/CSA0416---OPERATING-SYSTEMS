#!/bin/bash
set -e
gcc -std=c11 -O2 -Wall -Wextra rt_memlock_test.c -o rt_memlock_test
./rt_memlock_test
