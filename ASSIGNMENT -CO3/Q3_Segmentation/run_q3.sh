#!/bin/bash
set -e
gcc -std=c11 -O2 -Wall -Wextra segmentation_sim.c -o segmentation_sim
./segmentation_sim
