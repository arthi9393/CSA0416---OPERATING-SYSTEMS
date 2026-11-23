#!/usr/bin/env bash
# B1.1 - capture the state of the server. Save output with:  ./B1_observe_system.sh | tee B1_observe_output.txt
sec(){ printf '\n===== %s =====\n' "$*"; }
sec "ps (top 5 by CPU)";    ps aux --sort=-%cpu | head -6
sec "top (one batch run)";  top -b -n1 | head -15
sec "free -h";              free -h
sec "vmstat 1 5";           vmstat 1 5
sec "iostat -x 1 3";        (command -v iostat >/dev/null && iostat -x 1 3) || echo "install sysstat: sudo apt install sysstat"
sec "df -h";                df -h
sec "ss -tulpn";            ss -tulpn
sec "/proc/meminfo (head)"; head -5 /proc/meminfo
sec "/proc/loadavg";        cat /proc/loadavg
