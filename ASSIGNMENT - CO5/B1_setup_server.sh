#!/usr/bin/env bash
# B1.3 - set up users, service, Nginx and firewall on Ubuntu/Debian. Run with sudo. Read before running!
set -euo pipefail
apt-get update && apt-get install -y nginx python3-venv ufw sysstat

# Users and groups (A2.1)
id portal >/dev/null 2>&1 || useradd --system --create-home --home-dir /opt/portal --shell /usr/sbin/nologin portal
groupadd -f webops

# Application (copy app.py + requirements.txt from this package into /opt/portal/app first)
sudo -u portal python3 -m venv /opt/portal/venv
sudo -u portal /opt/portal/venv/bin/pip install -r /opt/portal/app/requirements.txt

install -m 644 B1_portal.service /etc/systemd/system/portal.service
systemctl daemon-reload && systemctl enable --now portal

install -m 644 B1_nginx_portal.conf /etc/nginx/sites-available/portal
ln -sf /etc/nginx/sites-available/portal /etc/nginx/sites-enabled/portal
rm -f /etc/nginx/sites-enabled/default
nginx -t && systemctl reload nginx

# Firewall: only SSH, HTTP, HTTPS (A2.2)
ufw default deny incoming
ufw default allow outgoing
ufw allow 22/tcp
ufw allow 80/tcp
ufw allow 443/tcp
ufw --force enable
ufw status verbose
