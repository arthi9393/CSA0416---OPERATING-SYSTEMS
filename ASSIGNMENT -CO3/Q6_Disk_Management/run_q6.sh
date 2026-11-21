#!/bin/bash
set -e
gcc -std=c11 -O2 -Wall -Wextra raid_calc.c -lm -o raid_calc
./raid_calc
lsblk
swapon --show || true
