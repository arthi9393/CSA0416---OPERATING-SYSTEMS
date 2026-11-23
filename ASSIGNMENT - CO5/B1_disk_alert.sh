#!/usr/bin/env bash
# Disk-space alert: warn when any mounted filesystem is above THRESHOLD percent.
# Usage: ./B1_disk_alert.sh [threshold]   (default 80)
set -euo pipefail
threshold="${1:-80}"
alert=0
while read -r fs size used avail pct mount; do
  usage="${pct%\%}"
  if [ "$usage" -ge "$threshold" ]; then
    echo "$(date '+%F %T') ALERT: $mount ($fs) is ${usage}% full (>= ${threshold}%)"
    logger -p user.warning -t disk_alert "$mount is ${usage}% full"
    alert=1
  fi
done < <(df -hP -x tmpfs -x devtmpfs -x overlay | awk 'NR>1')
[ "$alert" -eq 0 ] && echo "$(date '+%F %T') OK: all filesystems below ${threshold}%"
exit 0
