#!/bin/bash
set -e
gcc -std=c11 -O2 -Wall -Wextra -DPAGE_SIZE=1024 paging_todo.c -o paging_1024
gcc -std=c11 -O2 -Wall -Wextra -DPAGE_SIZE=2048 paging_todo.c -o paging_2048
./paging_1024
./paging_2048
getconf PAGESIZE
