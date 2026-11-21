#!/bin/bash
set -e
gcc -std=c11 -O2 -Wall -Wextra vm_demand_cow.c -o vm_demand_cow
./vm_demand_cow
