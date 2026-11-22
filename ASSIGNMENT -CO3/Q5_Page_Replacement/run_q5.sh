#!/bin/bash
set -e
gcc -std=c11 -O2 -Wall -Wextra page_replace_todo.c -o page_replace_todo
./page_replace_todo
