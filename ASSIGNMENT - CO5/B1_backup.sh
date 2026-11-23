#!/usr/bin/env bash
# Nightly backup of portal data, keeps the last 7 archives.
set -euo pipefail
SRC="${SRC:-/opt/portal/data}"; DEST="${DEST:-/var/backups/portal}"
mkdir -p "$DEST"
tar -czf "$DEST/portal-$(date +%F).tar.gz" -C "$(dirname "$SRC")" "$(basename "$SRC")"
ls -1t "$DEST"/portal-*.tar.gz | tail -n +8 | xargs -r rm --
echo "$(date '+%F %T') backup done"
